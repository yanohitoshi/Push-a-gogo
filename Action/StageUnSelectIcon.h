#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SpriteComponent;
class StageSelectSceneUI;

/*
@file StageUnSelectIcon.h
@brief 選択されていないstage選択アイコン画像を表示する
*/
class StageUnSelectIcon :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @parma 親クラスのポインタ
    @parma シーンのステータス
    @parma 描画する画像のファイルネーム
    */
    StageUnSelectIcon(StageSelectSceneUI* _owner, SceneState _state, const std::string& _spriteFileName);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~StageUnSelectIcon();

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // 背景用スプライトComponent
    SpriteComponent* sprite;
    // 自分のシーンステータス
    SceneState myState;
    // 描画するかどうか
    bool isVisible;

    // 各ステージアイコンのポジション
    const Vector3 FirstStagePosition;
    const Vector3 SecondStagePosition;
    const Vector3 ThirdStagePosition;
    const Vector3 FourthStagePosition;
    const Vector3 FinalStagePosition;

public:
    
    /*
    @brief	描画するかどうかをセット
    @param	_isVisible 描画するかどうか
    */
    void SetIsVisible(bool _isVisible) { isVisible = _isVisible; }
};

