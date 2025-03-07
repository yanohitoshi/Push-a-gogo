#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

/*
@file PlayerObjectStateJumpAttack.h
@brief ジャンプ攻撃開始からジャンプ攻撃終了状態に移行するまでを管理
*/
class PlayerObjectStateJumpAttack :
    public PlayerObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	@param _owner 親クラスのポインタ
	*/
	PlayerObjectStateJumpAttack(PlayerObject* _owner);

	/*
	@fn デストラクタ
	*/
	~PlayerObjectStateJumpAttack()override;

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return PlayerState　更新終了時のステータスを返す
	*/
	PlayerState Update(PlayerObject* _owner, float _deltaTime)override;

	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void Enter(PlayerObject* _owner, float _deltaTime)override;

private:
	// ターゲットとなる敵を捉えているかどうか
	bool isSelectingTargetEnemy;
	// ターゲットがいない場合のジャンプ攻撃のフレームをカウント
	int unSelectTargetEnemyFrameCount;
	// ターゲットがいない場合のジャンプ攻撃のスピード
	const float AttackSpeed;
	// ターゲットがいない場合のジャンプ攻撃を行う時間
	const int UnSelectTargetAttackTime;
	// ターゲットがいない場合のジャンプ攻撃を行う方向
	Vector3 jumpAttackDirection;

	// ターゲットとなる敵のポインタ
	GameObject* attackTarget;

};