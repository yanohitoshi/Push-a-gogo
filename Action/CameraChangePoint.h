#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class BoxCollider;

/*
@file CameraChangePoint.h
@brief カメラの画角を変更する場所を管理するクラス
*/
class CameraChangePoint :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	当たり判定用AABB
	@param	変更する間隔
	@param	オブジェクト判別用tag
	*/
	CameraChangePoint(const Vector3& _p, const AABB& _box,const Vector3& _changeOffset ,const Tag& _objectTag);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~CameraChangePoint();

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	@param	当たったGameObjectの当たり判定タグ
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

	// 当たり判定を行うクラス
	BoxCollider* boxCollider;

	// 変更する間隔
	Vector3 changeOffset;
};