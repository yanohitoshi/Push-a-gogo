#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

/*
@file BoxObject.h
@brief ボックスオブジェクトの生成と更新処理を行う
*/
class BoxObject : public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	objectのサイズ
	@param	オブジェクト判別用tag
	*/
	BoxObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag);
	~BoxObject();
	
	/*
	@fn 更新処理
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// 3Dモデルの描画を行うクラス
	Mesh* mesh;
	MeshComponent* meshComponent;

	// 当たり判定を行うクラス
	BoxCollider* boxCollider;
};

