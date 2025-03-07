//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateJumpLoop.h"
#include "SkeletalMeshComponent.h"

/*
@fn コンストラクタ
*/
PlayerObjectStateJumpLoop::PlayerObjectStateJumpLoop()
	: TurnValue(600.0f)
	, JumpCorrection(840.0f)
	, SwitchJumpCorrection(1320.0f)
{
}

/*
@fn デストラクタ
*/
PlayerObjectStateJumpLoop::~PlayerObjectStateJumpLoop()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return PlayerState　更新終了時のステータスを返す
*/
PlayerState PlayerObjectStateJumpLoop::Update(PlayerObject* _owner, float _deltaTime)
{
	// 滞空時間のカウントを数える
	++jumpLoopCount;

	// 重力にデルタタイムをかけた値を代入
	velocity.z -= PlayerObject::GetGravity() * _deltaTime;

	// 落下速度が規定値を超えていたら
	if (velocity.z <= MaxFallSpeed)
	{
		// 規定値に固定
		velocity.z = MaxFallSpeed;
	}

	// 移動速度にデルタタイムを掛けてそれをポジションに追加して更新
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// アニメーション変更フラグがtrueでかつZ軸の速度が0.0f以下になったら
	if (animChangeFlag == true && velocity.z <= 0.0f)
	{
		// ジャンプループのアニメーションを再生
		skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPLOOP));
		// 毎回再生をかけないようにフラグをfalseに
		animChangeFlag = false;
	}

	if (_owner->GetIsJumpAttck())
	{
		state = PlayerState::PLAYER_STATE_JUMP_ATTACK;
	}

	// 接地フラグがtrueでかつ移動入力がある状態でジャンプ攻撃を使用した後だったら
	if (_owner->GetOnGround() == true && _owner->GetInputFlag() && !_owner->GetIsAvailableJumpAttck())
	{
		// ステータスをローリングアニメーションを持つ着地状態にする
		state = PlayerState::PLAYER_STATE_JUMPEND_TO_RUN;
	}
	else if (_owner->GetOnGround() == true) // 接地フラグがtrueになったら
	{
		// ステータスを着地状態にする
		state = PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE;
	}

	CheckDeadFlag(_owner);

	CheckTimeOverFlag();

	// ownerの変数を更新
	_owner->SetVelocity(velocity);
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
void PlayerObjectStateJumpLoop::Input(PlayerObject* _owner, const InputState& _keyState)
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
void PlayerObjectStateJumpLoop::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// stateをジャンプループ状態にして保存
	state = PlayerState::PLAYER_STATE_JUMPLOOP;
	// アニメーション変更フラグを初期化
	animChangeFlag = true;
	// 滞空時間を測るカウントの初期化
	jumpLoopCount = 0;
	// ownerの速度をもらう
	velocity = _owner->GetVelocity();

	// 見た目上スムーズに遷移させるために前のステータスがジャンプ開始だったらジャンプ力をもらう
	if (_owner->GetNowState() == PlayerState::PLAYER_STATE_JUMPSTART)
	{
		// 前フレームのジャンプ力をもらう
		velocity.z = _owner->GetJumpPower();
	}

	// ownerの加速度変数の数値をもらう
	moveSpeed = _owner->GetMoveSpeed();

	// 加速度変数の数値が0.0f以下だったら
	if (moveSpeed <= 0.0f)
	{
		// 初速度を入れる
		moveSpeed = _owner->GetFirstMovePower();
	}

	// 入力が入らない値をもらう
	inputDeadSpace = _owner->GetDeadSpace();
}

/*
@fn 入力チェック関数処理関数
@param	_owner 親クラスのポインタ
@param	_keyState 入力情報
*/
void PlayerObjectStateJumpLoop::CheckInputProcess(PlayerObject* _owner, const InputState& _keyState)
{
	//実際に動かしたい軸がずれているので補正
	Vector3 axis = CheckControllerAxis(_keyState);

	// 取得した数値を見てデッドスペース外だったら入力処理を行う
	if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
	{
		// 入力がある場合の処理
		InputJumpMovableProcess(_owner,axis);
	}
	else // 取得した数値を見てデッドスペース内だったら減速処理を行う
	{
		// 入力がない場合の処理
		UninputMovableProcess(_owner);
	}

	// ジャンプ攻撃が可能かどうかを判定
	if (_owner->GetIsAvailableJumpAttck())
	{
		// ターゲットを選択しているまたはジャンプアタック中でなくかつターゲットを選択していない時
		if (_owner->GetIsSelectingTargetObject() || !_owner->GetIsJumpAttck() && !_owner->GetIsSelectingTargetObject())
		{
			bool isPressed = _keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
				_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
				_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
				_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed;

			// キー入力があれば
			if (isPressed)
			{
				// ジャンプアタックフラグをtrueにセット
				_owner->SetIsJumpAttck(true);
			}
		}
	}
}

/*
@fn 入力がない場合の処理関数
@param	_owner 親クラスのポインタ
*/
void PlayerObjectStateJumpLoop::UninputMovableProcess(PlayerObject* _owner)
{
	//　移動速度から空中用減速値を引く
	moveSpeed -= _owner->GetAirMovePower();

	// 移動速度が0.0f以下になったら
	if (moveSpeed <= 0.0f)
	{
		// マイナスにならないように0.0fに固定
		moveSpeed = 0.0f;
	}

	// ownerの方向ベクトルに移動速度を掛けて移動ベクトルを更新
	velocity.x = _owner->GetCharaForwardVec().x * moveSpeed;
	velocity.y = _owner->GetCharaForwardVec().y * moveSpeed;

	// 移動入力フラグをfalseにセット
	_owner->SetInputFlag(false);
}