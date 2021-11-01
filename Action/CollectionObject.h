#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class MeshComponent;
class BoxCollider;
class Mesh;

enum class CollectionTag
{
	FIRST,
	SECOND,
	THIRD
};

class CollectionObject :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	オブジェクト判別用tag
	*/
	CollectionObject(const Vector3& _pos, const Tag& _objectTag, CollectionTag _collectionTag);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~CollectionObject()override;

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
	@fn 回転処理関数
	*/
	void RotationProcess(float _angle,Vector3 _axis);

	/*
	@fn 可動処理関数
	*/
	void Movable(float _deltaTime);

	/*
	@fn 可動処理関数
	*/
	void Collected(float _deltaTime);

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	@param	当たったGameObjectの当たり判定タグ
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

	// 3Dモデルの描画を行うクラス
	MeshComponent* meshComponent;
	Mesh* mesh;
	BoxCollider* boxCollider;
	CollectionTag collectionTag;

	float collectedRotationAngle;
	bool isCollected;
	int collectedCount;
	int frameCount;
	float value;
	float rate;

public:

	bool GetIsCollected() { return isCollected; }

	CollectionTag GetCollectionTag() { return collectionTag; }
};

