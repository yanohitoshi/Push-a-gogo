#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;
/*
@file NextSceneObject.h
@brief NextSceneObjectの生成と更新を行う
*/
class NextSceneObject :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	オブジェクト判別用tag
	*/
	NextSceneObject(const Vector3& _pos, const Tag& _objectTag);
	~NextSceneObject();
	
	/*
	@fn 更新処理
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;


private:
	
	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	// 3Dモデルの描画を行うクラス
	MeshComponent* meshComponent;
	Mesh* mesh;

	// 当たり判定を行うクラス
	BoxCollider* boxCollider;
	// 生成されたときのポジションを保存するよう
	Vector3 firstPos;
	// 回転する際の角度変数
	float angle;

};

