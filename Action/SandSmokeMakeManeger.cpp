#include "SandSmokeMakeManeger.h"
#include "ParticleEffectBase.h"
#include "SandSmokeParticle.h"

SandSmokeMakeManeger::SandSmokeMakeManeger(GameObject* _owner)
	:GameObject(false,Tag::PARTICLE)
	, ShiftPositionX(40.0f)
	, MaxShiftPositionY(1500.0f)
	, MinShiftPositionY(900.0f)
	, BigWallSize(1600.0f)
	, SmallWallSize(1000.0f)
	, RandValueX(500)
	, BigRandValueY(40000)
	, SmallRandValueY(20000)
	, RandValueZ(100)
	, CorrectionRandValue(10.0f)
	, GenerateFrequency(3)
	, SmallWallMaxEffect(10)
	, BigWallMaxEffect(20)
{
	// メンバー変数の初期化
	owner = _owner;
	position = owner->GetPosition();
	ownerSize = owner->GetScaleVec();
	frameCount = 0;
	// 中心に設置するために少しずらす
	position.x -= ShiftPositionX;

	// ownerの大きさを見てそれぞれの数値分ずらして中心に設置（※現状2種なのでこうしてるが改良の余地あり）
	// 小さいサイズの時
	if (ownerSize.y == SmallWallSize)
	{
		position.y -= MinShiftPositionY;
	}
	// 大きいサイズの時
	if (ownerSize.y == BigWallSize)
	{
		position.y -= MaxShiftPositionY;
	}
}

SandSmokeMakeManeger::~SandSmokeMakeManeger()
{
}

void SandSmokeMakeManeger::UpdateGameObject(float _deltaTime)
{
	// ownerの速度を見て動いている時
	if (owner->GetVelocity().z != 0)
	{
		// パーティクルを有効化
		particleState = ParticleState::PARTICLE_ACTIVE;
	}
	else
	{
		// パーティクルを無効化
		particleState = ParticleState::PARTICLE_DISABLE;
	}

	// パーティクルの状態を見て
	switch (particleState)
	{
		// 無効状態だったらbreak
	case (PARTICLE_DISABLE):
		break;

		// 有効状態だったら
	case PARTICLE_ACTIVE:

		// フレームカウントを数える
		++frameCount;

		// 小さいサイズの時
		if (ownerSize.y == SmallWallSize)
		{
			// 3フレームに一度
			if (frameCount % GenerateFrequency == 0)
			{
				// エフェクトを10個生成
				for (int efectCount = 0; efectCount < SmallWallMaxEffect; efectCount++)
				{
					// ランダムな値を生成
					Vector3 randV((rand() % RandValueX) / CorrectionRandValue, (rand() % SmallRandValueY) / CorrectionRandValue, (rand() % RandValueZ) / CorrectionRandValue);

					// ランダムで出た値に補正をかける
					velocity = randV * 0.1f;

					// 速度の最低値を設定
					velocity.x = -2.0f;
					velocity.z = 1.0f;
					velocity.y = 0.0f;

					//発生位置を設定
					Vector3 pos = position;
					//ランダムな値を渡す
					pos = pos + randV;
					//particleを生成
					new SandSmokeParticle(pos, velocity);

				}
			}
		}

		// 大きいサイズの時
		if (ownerSize.y == BigWallSize)
		{
			// 3フレームに一度
			if (frameCount % GenerateFrequency == 0)
			{
				// エフェクトを20個生成
				for (int efectCount = 0; efectCount < BigWallMaxEffect; efectCount++)
				{
					// ランダムな値を生成
					Vector3 randV((rand() % RandValueX) / CorrectionRandValue, (rand() % BigRandValueY) / CorrectionRandValue, (rand() % RandValueZ) / CorrectionRandValue);
					
					// ランダムで出た値に補正をかける
					velocity = randV * 0.1f;
					// 速度の最低値を設定
					velocity.x = -2.0f;
					velocity.z = 1.0f;

					//発生位置を設定
					Vector3 pos = position;
					//ランダムな値を渡す
					pos = pos + randV;
					//particleを生成
					new SandSmokeParticle(pos, velocity);

				}
			}

		}
		break;
	}


}

