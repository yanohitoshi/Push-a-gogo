#include "JumpParticleEffectManeger.h"
#include "JumpParticleEffect.h"
#include "PlayerObject.h"

JumpParticleEffectManeger::JumpParticleEffectManeger(GameObject* _owner)
	: GameObject(false, Tag::PARTICLE)
{
	particleState = ParticleState::PARTICLE_DISABLE;
	owner = _owner;
	position = Vector3(0.0f,0.0f,0.0f);
	tmpVelZ = 0.0f;
	generateFlag = false;
}

JumpParticleEffectManeger::~JumpParticleEffectManeger()
{
}

void JumpParticleEffectManeger::UpdateGameObject(float _deltaTime)
{


	if (PlayerObject::GetChackIsJumpingFlag() == true && 0.0f == tmpVelZ )
	{
		particleState = ParticleState::PARTICLE_ACTIVE;
		generateFlag = true;
	}
	else
	{
		particleState = ParticleState::PARTICLE_DISABLE;
	}


	switch (particleState)
	{

	case (PARTICLE_DISABLE):
		break;

	case PARTICLE_ACTIVE:


		//particleが発生するフレームの条件式を書く
		if (generateFlag == true)
		{
			position = owner->GetPosition();

			for (int i = 0; i < 3; i++)
			{
				Vector3 randV((rand() % 50) / 10.0f, (rand() % 50) / 10.0f, 0.0f);
				velocity = randV * 0.1f;
				//発生位置を設定
				Vector3 vel = Vector3(0.0f,0.0f,1.0f);
				
				position = position + randV;

				//particleを生成
				new JumpParticleEffect(position, vel);
			}
			generateFlag = false;
		}

		particleState = ParticleState::PARTICLE_DISABLE;

		break;
	}

	tmpVelZ = owner->GetVelocity().z;

}
