//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateExplosion.h"
#include "MeshComponent.h"
#include "SoundEffectComponent.h"

ExplosionObjectStateExplosion::ExplosionObjectStateExplosion(ExplosionObjectBase* _owner)
	: ExplosionTime(10)
{
	soundEffectComponent = new SoundEffectComponent(_owner, "Assets/Sound/SoundEffect/Explosion/Explosion.wav");
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return ExplosionObjectState　更新終了時のステータスを返す
*/
ExplosionObjectState ExplosionObjectStateExplosion::Update(ExplosionObjectBase* _owner, float _deltaTime)
{
	++explosionCount;
	if (explosionCount >= ExplosionTime)
	{
		state = ExplosionObjectState::RESPAWN;
	}

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void ExplosionObjectStateExplosion::Enter(ExplosionObjectBase* _owner, float _deltaTime)
{
	// ステータスを爆発状態に変更
	state = ExplosionObjectState::EXPLOSION;
	// 変数初期化
	explosionCount = 0;
	meshComponent = _owner->GetMeshComponent();
	meshComponent->SetVisible(false);
	_owner->SetIsStartExplosion(false);
	_owner->SetIsExplode(true);

	// 効果音を鳴らす
	soundEffectComponent->Play();
}