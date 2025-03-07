//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnhancedEnemyStateFlinch.h"

/*
@fn コンストラクタ
*/
EnhancedEnemyStateFlinch::EnhancedEnemyStateFlinch()
	: EndTime(60)
	, FirstBlowAwayPower(100.0f)
	, BlowAwayPower(1.2f)
	, MaxSpeed(500.0f)
{
}

/*
@fn デストラクタ
*/
EnhancedEnemyStateFlinch::~EnhancedEnemyStateFlinch()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return EnemyState 次のステータス
*/
EnemyState EnhancedEnemyStateFlinch::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	++flinchCount;

	// 加速度
	moveSpeed *= BlowAwayPower;

	// 最大速度に到達していたら最大速度に固定する
	if (moveSpeed >= MaxSpeed)
	{
		moveSpeed = MaxSpeed;
	}

	// 作用する速度ベクトル計算
	velocity = blowAwayDirection * moveSpeed;

	// positionに速度を足してキャラクターを動かす
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// 時間が来たらリスポーン
	if (flinchCount >= EndTime)
	{
		_owner->SetIsFlinch(false);
		state = EnemyState::ENEMY_STATE_IDLE;
	}

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void EnhancedEnemyStateFlinch::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_FLINCH));
	// stateを待機状態にして保存
	state = EnemyState::ENEMY_STATE_FLINCH;

	// ステータスを無効状態にする
	_owner->SetState(State::Disabling);

	// カウント初期化
	flinchCount = 0;
	// 吹っ飛ぶ方向を計算
	blowAwayDirection = _owner->GetPosition() - _owner->GetDefeatedObjectPosition();

	// 長さが0に近くなかったら
	if (!Math::NearZero(blowAwayDirection.Length()))
	{
		// 正規化
		blowAwayDirection.Normalize();
	}

	// 上下方向を0に固定
	blowAwayDirection.z = 0.0f;
	// 移動速度を初速にする
	moveSpeed = FirstBlowAwayPower;
}