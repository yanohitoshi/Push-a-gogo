#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SphereCollider;
class EnemyObjectBase;

class EnemyAttackArea :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	親クラスのポインタ
	*/
	EnemyAttackArea(const Tag& _objectTag, EnemyObjectBase* _ownerEnemy);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~EnemyAttackArea();

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
	@param	当たり判定タグ
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

	// 当たり判定を行うクラス
	SphereCollider* sphereCollider;
	// 親となるクラスのポインタ
	EnemyObjectBase* ownerEnemy;

	// 無効化状態の時間を数えるカウント
	int disableCount;
	// 攻撃判定エリアが有効かどうか
	bool isEnable;

	// 攻撃エリアのサイズ
	const float AttackArea;
	// 有効に切り替える時間
	const int EnableTime;
};