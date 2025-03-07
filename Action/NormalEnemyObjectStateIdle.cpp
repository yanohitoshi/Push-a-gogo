//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "NormalEnemyObjectStateIdle.h"

/*
@fn コンストラクタ
*/
NormalEnemyObjectStateIdle::NormalEnemyObjectStateIdle()
{
}

/*
@fn デストラクタ
*/
NormalEnemyObjectStateIdle::~NormalEnemyObjectStateIdle()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return EnemyState 次のステータス
*/
EnemyState NormalEnemyObjectStateIdle::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// 死亡状態だったら
	if (_owner->GetIsDead())
	{
		// ステータスを死亡状態に
		state = EnemyState::ENEMY_STATE_DEAD;
	}

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void NormalEnemyObjectStateIdle::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// stateを待機状態にして保存
	state = EnemyState::ENEMY_STATE_IDLE;
	// ステータスを有効化
	_owner->SetState(State::Active);
}