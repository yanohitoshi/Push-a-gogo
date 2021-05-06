#include "SecondStageUI.h"
#include "Renderer.h"
#include "CountDownFont.h"
#include "JumpTutorialParticl.h"
#include "MoveTutorialParticl.h"
#include "StartCountDownSprite.h"
#include "TimeUpSprite.h"
#include "ContinueSprite.h"
#include "GameOverSprite.h"
#include "PlayerObject.h"

// 静的メンバー初期化
bool SecondStageUI::timeOverFlag = false;
bool SecondStageUI::countStartFlag = false;

SecondStageUI::SecondStageUI(PlayerObject* _playerObject)
	: GameObject(false, Tag::UI)
	, SCENE_TIME(120)
{
	// カウントダウン
	new CountDownFont(SCENE_TIME);
	// start時のカウントダウン
	new StartCountDownSprite();
	// タイムアップ時のsprite
	new TimeUpSprite();
	// コンティニュー選択時のsprite
	new ContinueSprite();
	// GameOver時のsprite
	new GameOverSprite();
}

SecondStageUI::~SecondStageUI()
{
	// 静的メンバー初期化
	timeOverFlag = false;
	countStartFlag = false;
}

void SecondStageUI::UpdateGameObject(float _deltaTime)
{
}
