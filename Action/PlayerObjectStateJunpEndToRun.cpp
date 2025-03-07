//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateJunpEndToRun.h"
#include "SkeletalMeshComponent.h"

/*
@fn コンストラクタ
*/
PlayerObjectStateJunpEndToRun::PlayerObjectStateJunpEndToRun()
	: UnInputDecelerationForce(75.0f)
	, InputDecelerationForce(0.7f)
{
}

/*
@fn デストラクタ
*/
PlayerObjectStateJunpEndToRun::~PlayerObjectStateJunpEndToRun()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return PlayerState　更新終了時のステータスを返す
*/
PlayerState PlayerObjectStateJunpEndToRun::Update(PlayerObject* _owner, float _deltaTime)
{
	// 着地時の減衰値を掛ける
	velocity *= InputDecelerationForce;
	// 移動速度にデルタタイムを掛けてそれをポジションに追加して更新
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// アニメーションの再生が終わっていたら
	if (!skeletalMeshComponent->IsPlaying())
	{
		// 移動入力があったら
		if (_owner->GetInputFlag())
		{
			// ステータスを走り出し状態にする
			state = PlayerState::PLAYER_STATE_RUN_START;
		}
		else
		{
			// ステータスを待機状態にする
			state = PlayerState::PLAYER_STATE_IDLE;
		}
	}

	// ジャンプフラグもしくはスイッチジャンプフラグがtrueだったら
	if (_owner->GetJumpFlag() || _owner->GetSwitchJumpFlag())
	{
		// ステータスをジャンプ開始状態にする
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	// ジャンプフラグがfalseかつ接地状態でも無ければ
	if (!_owner->GetJumpFlag() && !_owner->GetOnGround())
	{
		// ステータスをジャンプループ状態にする
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}

	// 死亡状態チェック
	CheckDeadFlag(_owner);
	// 時間切れチェック
	CheckTimeOverFlag();

	// ownerの変数を更新
	_owner->SetMoveSpeed(moveSpeed);

	// 更新されたstateを返す
	return state;
}

/*
@fn インプット
@brief	stateに応じて入力処理を行う
@param	_owner 親クラスのポインタ
@param	_keyState 入力情報
*/
void PlayerObjectStateJunpEndToRun::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// 入力可能状態かを見る
	if (_owner->GetIsAvailableInput())
	{
		// 入力情報チェック処理
		CheckInputProcess(_owner,_keyState);
	}
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void PlayerObjectStateJunpEndToRun::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPEND_TO_RUN),1.4f);
	// stateを着地ローリング状態にして保存
	state = PlayerState::PLAYER_STATE_JUMPEND_TO_RUN;

	// ownerの移動速度をもらう
	moveSpeed = _owner->GetMoveSpeed();
	// ownerの移動ベクトルをもらう
	velocity = _owner->GetVelocity();
	// 着地状態なのでZ軸は0に固定
	velocity.z = 0.0f;
	// 入力が入らない値をもらう
	inputDeadSpace = _owner->GetDeadSpace();

	// ownerのジャンプ力をリセット
	_owner->SetJumpPower(_owner->GetFirstJumpPower());
	// ジャンプボタン利用を可能状態にセット
	_owner->SetIsAvailableJumpKey(true);
	// ジャンプフラグをfalseにセット
	_owner->SetJumpFlag(false);
	// ジャンプ攻撃系フラグ初期化
	_owner->SetSwitchJumpFlag(false);
	_owner->SetIsAvailableJumpAttck(true);

}

/*
@fn 入力チェック関数処理関数
@param	_owner 親クラスのポインタ
@param	_keyState 入力情報
*/
void PlayerObjectStateJunpEndToRun::CheckInputProcess(PlayerObject* _owner, const InputState& _keyState)
{
	//実際に動かしたい軸がずれているので補正
	Vector3 axis = CheckControllerAxis(_keyState);

	// 取得した数値を見てデッドスペース外だったら入力処理を行う
	if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
	{
		// 入力がある場合の処理
		InputMovableProcess(_owner, axis);
	}
	else // デッドスペース内だったら減速処理を行う
	{
		// 入力がない場合の処理
		UninputMovableProcess(_owner);
	}

	// ジャンプを割り当てられているコントローラーのボタンが押されたらもしくはジャンプスイッチが押されたら
	if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed ||
		_owner->GetSwitchJumpFlag() == true)
	{
		// ジャンプ準備
		JumpTransitionProcess(_owner);
	}
}

/*
@fn 入力がある場合の処理関数
@param	_owner 親クラスのポインタ
@param	_axis 補正済みのアナログスティック情報
*/
void PlayerObjectStateJunpEndToRun::InputMovableProcess(PlayerObject* _owner, Vector3 _axis)
{
	// 前のフレームのキャラクターの前方ベクトルを保存
	Vector3 tmpForward = _owner->GetCharaForwardVec();

	// 方向キーの入力値とカメラの向きから、移動方向を決定
	Vector3 forward = _owner->GetForwardVec() * _axis.x + _owner->GetRightVec() * _axis.y;
	if (!Math::NearZero(forward.Length()))
	{
		// 正規化
		forward.Normalize();
	}

	// 移動速度に加速度定数を足す
	moveSpeed += _owner->GetMovePower();

	// 移動速度が最大値を超えていたら
	if (moveSpeed >= MaxMoveSpeed)
	{
		// 移動速度を最大値に固定
		moveSpeed = MaxMoveSpeed;
	}


	// 移動ベクトルに速度をかける
	velocity.x = forward.x * moveSpeed;
	velocity.y = forward.y * moveSpeed;

	// 回転処理
	RotationProcess(_owner, forward, tmpForward);

	// ownerの速度変数を更新
	_owner->SetMoveSpeed(moveSpeed);

}

/*
@fn 入力がない場合の処理関数
@param	_owner 親クラスのポインタ
*/
void PlayerObjectStateJunpEndToRun::UninputMovableProcess(PlayerObject* _owner)
{
	// 速度が0.0f以上だったら
	if (moveSpeed >= 0.0f)
	{
		// 速度から減速定数を引く
		moveSpeed -= UnInputDecelerationForce;
	}

	// 移動ベクトルの変更がないのでownerの前方ベクトルをもらいそのベクトルに速度をかける
	velocity.x = _owner->GetCharaForwardVec().x * moveSpeed;
	velocity.y = _owner->GetCharaForwardVec().y * moveSpeed;

	// 移動入力フラグをfalseにセット
	_owner->SetInputFlag(false);

}

/*
@fn ジャンプ状態に遷移するための準備処理関数
@param	_owner 親クラスのポインタ
*/
void PlayerObjectStateJunpEndToRun::JumpTransitionProcess(PlayerObject* _owner)
{
	// ジャンプフラグをtrueにセット
	_owner->SetJumpFlag(true);
}