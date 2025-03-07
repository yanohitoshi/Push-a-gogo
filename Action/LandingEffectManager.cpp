//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "LandingEffectManager.h"
#include "LandingEffect.h"
#include "PlayerObject.h"

/*
@fn コンストラクタ
@param	_owner 親クラスのポインタ
*/
LandingEffectManager::LandingEffectManager(PlayerObject* _owner)
	: GameObject(false, Tag::PARTICLE)
	, MaxEffects(8)
{
	// メンバー変数の初期化	
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f, 0.0f, 0.0f);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
LandingEffectManager::~LandingEffectManager()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void LandingEffectManager::UpdateGameObject(float _deltaTime)
{
	// 前のフレームでZ軸の速度が0.0fでなくこのフレームでのZ軸の速度0.0fでかつジャンプフラグがfalseだったら
	if (owner->GetNowState() == PlayerState::PLAYER_STATE_JUMPSTART || owner->GetNowState() == PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE ||
		owner->GetNowState() == PlayerState::PLAYER_STATE_JUMPEND_TO_RUN)
	{
		// パーティクルを有効化
		particleState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		// パーティクルを無効化
		particleState = ParticleState::PARTICLE_DISABLE;
	}

	// ステータス状態を見る
	switch (particleState)
	{
		// 無効状態だったらbreak
	case (PARTICLE_DISABLE):
		generateEffectsFlag = true;
		break;
		// 有効状態だったら
	case PARTICLE_ACTIVE:

		// エフェクトの生成
		ActiveEffect();
		break;
	}
}

/*
@fn エフェクトがアクティブ時の処理関数
*/
void LandingEffectManager::ActiveEffect()
{
	if (generateEffectsFlag)
	{
		// ownerのポジションを得る
		position = owner->GetPosition();

		// 8個生成
		for (int efectCount = 0; efectCount < MaxEffects; efectCount++)
		{
			// それぞれのエフェクトの方向を計算する処理
			CalculatingDirectionProcess(efectCount, velocity);

			//particleを生成
			new LandingEffect(position, velocity);
		}

		generateEffectsFlag = false;
	}
}

/*
@fn エフェクトを飛ばす方向計算処理関数
*/
void LandingEffectManager::CalculatingDirectionProcess(int _index, Vector3& _velocity)
{
	// 八方向に動かすのでそれぞれに方向ベクトルを渡す
	if (_index == 0)
	{
		_velocity = Vector3::UnitX;
	}

	if (_index == 1)
	{
		_velocity = Vector3::UnitY;
	}

	if (_index == 2)
	{
		_velocity = Vector3::NegUnitX;
	}

	if (_index == 3)
	{
		_velocity = Vector3::NegUnitY;
	}

	if (_index == 4)
	{
		_velocity = Vector3::UnitX + Vector3::UnitY;
	}

	if (_index == 5)
	{
		_velocity = Vector3::UnitX + Vector3::NegUnitY;
	}

	if (_index == 6)
	{
		_velocity = Vector3::NegUnitX + Vector3::UnitY;
	}

	if (_index == 7)
	{
		_velocity = Vector3::NegUnitX + Vector3::NegUnitY;
	}
}