#pragma once

#include "GameObject.h"
#include <glew.h>

class BoxCollider;
class Mesh;
class ChangeColorMeshComponent;

/*
@file SwitchBlock.h
@brief スイッチの生成と更新処理を行う
*/
class SwitchBlock : public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	objectのサイズ
	@param	オブジェクト判別用tag
	*/
	SwitchBlock(GameObject* _owner, const Vector3& _size, const Tag& _objectTag);
	~SwitchBlock();

	/*
	@fn 更新処理
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	// 区画ごとに分かれたswitchがすべて押されたかどうかチェックする関数
	void ChackOnFlag(Tag& _Tag);

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
		動く床と接している時にその速度をもらうための
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;
	
	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
		プレイヤーの足元判定とのOnCollision
	@param	当たったGameObject
	*/
	void PlayerFootOnCollision(const GameObject& _hitObject);

	// 色変更機能付きMeshComponent
	ChangeColorMeshComponent* meshComponent;
	// 動く床と接している時にその速度をもらうためのCollider
	BoxCollider* boxCollider;
	// プレイヤーとの足元判定用Collider
	BoxCollider* PlayerFootBoxCollider;
	// メッシュからAABBの最大点最小点を得るときに使う
	Mesh* mesh;
	// Switchが利用可能か
	bool isAvailableSwitch;
	// Switchの初期ポジション保存用
	Vector3 initPosition;
	// playerがswitchに乗っているかどうか
	bool isOnPlayer;
	bool isHitPlayer;
	// 押すのを止めるかどうか
	bool pushStop;
	// 色を変えるかどうか
	bool changeColorFlag;
	// 前のフレームで色変更が行われたかどうか
	bool tmpChangeColorFlag;
	// switchの停止位置
	float stopPoint;

};
