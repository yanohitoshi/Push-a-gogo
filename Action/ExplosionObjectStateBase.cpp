#include "ExplosionObjectStateBase.h"

void ExplosionObjectStateBase::RotationProcess(ExplosionObjectBase* _owner, float _angle, Vector3 _axis)
{
	//_axis軸を_angle度回転させる
	float radian = Math::ToRadians(_angle);
	Quaternion rot = _owner->GetRotation();
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	_owner->SetRotation(target);
}

void ExplosionObjectStateBase::VerticalMove(ExplosionObjectBase* _owner, float _deltaTime)
{
	++frameCount;

	if (frameCount % 45 == 0)
	{
		++angle;
		rate = Math::Cos(angle);
	}

	velocity.z = rate * VerticalMoveSpeed;

	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
}