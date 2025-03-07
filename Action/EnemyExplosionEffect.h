#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

// クラスの前方宣言
class EnemyObjectBase;

/*
@file EnemyExplosionEffect.h
@brief 爆発エフェクトの更新を行うクラス
*/
class EnemyExplosionEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn コンストラクタ
    @param	親となるクラスのポインタ
    @param	ポジション
    @param	移動速度
    */
    EnemyExplosionEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _velocity);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~EnemyExplosionEffect()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // 毎フレーム足すscale値 
    const float AddScale;
    // 毎フレーム引くalpha値
    const float SubAlpha;
    // エフェクトの色
    const Vector3 EffectColor;

    // ランダムな速度を得るための定数
    const int SpeedRandValue;
    // ランダムな速度の補正値
    const float SpeedCorrection;
};

