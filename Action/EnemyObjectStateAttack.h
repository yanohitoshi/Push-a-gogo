#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectStateBase.h"

/*
@file EnemyObjectStateAttack.h
@brief 敵オブジェクトの攻撃状態を管理するクラス
*/
class EnemyObjectStateAttack :
    public EnemyObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	EnemyObjectStateAttack();

	/*
	@fn デストラクタ
	*/
	~EnemyObjectStateAttack()override;

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return EnemyState 次のステータス
	*/
	EnemyState Update(EnemyObjectBase* _owner, float _deltaTime)override;

	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void Enter(EnemyObjectBase* _owner, float _deltaTime)override;

private:

	// 追跡対象となるオブジェクトを保存するポインタ変数
	GameObject* trackingObject;
	// 追跡用の回転ベクトル
	Vector3 trackingRotationVec;
	// 初期ポジション
	Vector3 firstPosition;
	// 攻撃速度
	const float AttackSpeed;
};