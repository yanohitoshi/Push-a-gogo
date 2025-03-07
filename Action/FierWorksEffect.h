#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"
#include "CrystalEffectManager.h"

/*
@file FierWorksEffect.h
@brief 花火エフェクトの更新を行う
*/
class FierWorksEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn コンストラクタ
    @param	ポジション
    @param	移動速度
    @param	何色か判定用Tag
    */
    FierWorksEffect(const Vector3& _pos, const Vector3& _velocity , CrystalColor _crystalColor);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~FierWorksEffect()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    
    /*
    @fn フェードイン関数
    */
    void FadeIn();

    /*
    @fn 速度抑制関数
    */
    void CheckSpeed();

    // フェードインフラグ
    bool inFlag;

    // alpha値の初期値
    const float InitAlpha;
    // scale値の初期値
    const float InitScale;
    // 移動速度定数
    const float MoveSpeed;
    // 速度に減速をかける際の定数
    const float SubSpeed;
    // フェードイン中の毎フレーム足すscale値 
    const float FadeInAddScale;
    // フェードアウト中の毎フレーム足すscale値 
    const float FadeOutAddScale;
    // 毎フレーム足すAlpha値
    const float AddAlpha;
    // 毎フレーム引くAlpha値
    const float SubAlpha;
    // Alpha値の最大値
    const float MaxAlpha;
    // フェードアウトするときの速度の定数
    const float VelocityAtFadeOut;

    // フェードアウトに切り替えるタイミング定数
    const int ChangeFadeOutTime;

    // 白色の場合の色の値定数
    const Vector3 WhiteValue;
    // 赤色の場合の色の値定数
    const Vector3 RedValue;
    // 青色の場合の色の値定数
    const Vector3 BlueValue;
    // 緑色の場合の色の値定数
    const Vector3 GreenValue;
};