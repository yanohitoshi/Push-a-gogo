//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectStateAttack.h"

/*
@fn コンストラクタ
*/
EnemyObjectStateAttack::EnemyObjectStateAttack()
	: AttackSpeed(100.0f)
{
}

/*
@fn デストラクタ
*/
EnemyObjectStateAttack::~EnemyObjectStateAttack()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return EnemyState 次のステータス
*/
EnemyState EnemyObjectStateAttack::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// アニメーションの再生が終わっていたら
	if (!skeletalMeshComponent->IsPlaying())
	{
		_owner->SetIsAttack(false);
		state = EnemyState::ENEMY_STATE_IDLE;
		RotationProcess(_owner, trackingRotationVec, _owner->GetCharaForwardVec());
	}
	else
	{
		velocity = trackingRotationVec * AttackSpeed;
		// positionに速度を足してキャラクターを動かす
		_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
	}

	// オーナーが死亡状態か判定
	if (_owner->GetIsDead())
	{
		state = EnemyState::ENEMY_STATE_DEAD;
	}

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void EnemyObjectStateAttack::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_ATTACK));
	// stateを待機状態にして保存
	state = EnemyState::ENEMY_STATE_ATTACK;

	// ステータスをActiveにする
	_owner->SetState(State::Active);

	// 今のポジションから追跡ターゲットのポジションへの方向ベクトルを計算
	trackingRotationVec = _owner->GetAttackObjectPosition() - _owner->GetPosition();
	// 上下移動させないので0で固定
	trackingRotationVec.z = 0.0f;

	// 長さが0に近くなかったら
	if (!Math::NearZero(trackingRotationVec.Length()))
	{
		// 正規化
		trackingRotationVec.Normalize();
	}

	// 回転処理
	RotationProcess(_owner, trackingRotationVec, _owner->GetCharaForwardVec());
}