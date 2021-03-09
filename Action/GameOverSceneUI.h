#pragma once
#include "GameObject.h"

class SpriteComponent;

/*
@file GameOverSceneUI.h
@brief GameOverScene画面でのUIの表示を行う
*/

class GameOverSceneUI :
    public GameObject
{
public:

    GameOverSceneUI();
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~GameOverSceneUI();
    
    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // GameOver画像表示用sprite
    SpriteComponent* sprite;

};

