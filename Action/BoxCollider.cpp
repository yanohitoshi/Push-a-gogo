﻿//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "BoxCollider.h"
#include "Math.h"
#include "GameObject.h"
#include "Collision.h"
#include "Game.h"

/*
@brief	コンストラクタ
@param	アタッチするゲームオブジェクトのポインタ
@param	他のオブジェクトと当たった時に呼ばれる関数ポインタ(GetOnCollisionFuncを呼ぶ)
@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
@param	当たり判定時に、めり込みから動かす処理の優先度を決める数値
*/
BoxCollider::BoxCollider(GameObject* _owner, PhysicsTag tag, onCollisionFunc _func, int _updateOrder, int _collisionOrder)
	: ColliderComponent(_owner, tag,_updateOrder, _collisionOrder)
	, objectBox({ Vector3::Zero,Vector3::Zero })
	, worldBox({ Vector3::Zero,Vector3::Zero })
	, shouldRotate(true)
{
	PHYSICS->AddBoxes(this, _func);
}

/*
@brief	デストラクタ
*/
BoxCollider::~BoxCollider()
{
	PHYSICS->RemoveBoxes(this);
}

/*
@brief	Transformのワールド変換
*/
void BoxCollider::OnUpdateWorldTransform()
{
	RefreshWorldTransform();
	PHYSICS->HitCheck(this);
}

/*
@brief	Transformのワールド変換
押し戻しが行われた直後にObjectのworldBoxを更新
*/
void BoxCollider::RefreshWorldTransform()
{
	worldBox = objectBox;

	worldBox.min = (objectBox.min * owner->GetScaleVec());
	worldBox.max = (objectBox.max * owner->GetScaleVec());

	if (shouldRotate)
	{
		worldBox.Rotate(owner->GetRotation());
	}

	worldBox.min += owner->GetPosition();
	worldBox.max += owner->GetPosition();
}