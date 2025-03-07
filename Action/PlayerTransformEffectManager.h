#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file PlayerTransformEffectManager.h
@brief プレイヤーのジャンプアタック状態へ変形時のエフェクトの生成を行うクラス
*/
class PlayerTransformEffectManager :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @param	_owner 親クラスのポインタ
    */
    PlayerTransformEffectManager(PlayerObject* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~PlayerTransformEffectManager()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    /*
    @fn エフェクトがアクティブ時の処理関数
    */
    void ActiveEffect();

    /*
    @fn エフェクト生産処理関数
    */
    void GenerateEffect();

    // 親のGameObject保存用変数
    PlayerObject* owner;
    // particleの状態管理用変数
    ParticleState particleState;
    // 生成するエフェクトのポジション
    Vector3 effectPosition;
    // 生成時間を数える
    int frameCount;
    // エフェクトの数を数える
    int effectCount;
    // 1度だけ生成する用の生成フラグ変数
    bool generateFlag;

    // Z軸をずらす定数
    const float OffsetPositionZ;
};

