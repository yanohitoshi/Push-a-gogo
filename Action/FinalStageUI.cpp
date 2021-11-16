//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "FinalStageUI.h"
#include "Renderer.h"
#include "CountDownFont.h"
#include "StartCountDownSprite.h"
#include "TimeUpSprite.h"
#include "ContinueSprite.h"
#include "GameOverSprite.h"
#include "GameClearSprite.h"
#include "PlayerObject.h"
#include "SkyBoxObject.h"
#include "CollectionUI.h"
#include "CollectionObject.h"
/*
@fn コンストラクタ
@brief  objectの生成を行う
@param	_playerObject プレイヤークラスのポインタ
*/
FinalStageUI::FinalStageUI(PlayerObject* _playerObject, CollectionObject* _first, CollectionObject* _second, CollectionObject* _third)
	: GameObject(false, Tag::UI)
	, SceneTime(500)
{
	// カウントダウン
	new CountDownFont(SceneTime);
	// start時のカウントダウン
	new StartCountDownSprite();
	// タイムアップ時のsprite
	new TimeUpSprite();
	// コンティニュー選択時のsprite
	new ContinueSprite();
	// GameOver時のsprite
	new GameOverSprite();
	// GameClear時のsprite
	new GameClearSprite(_playerObject);

	skyBox = new SkyBoxObject(false, Tag::UI);

	playerObject = _playerObject;

	firstCollectionUI = new CollectionUI(_first);
	secondCollectionUI = new CollectionUI(_second);
	thirdCollectionUI = new CollectionUI(_third);

	clearCount = 0;
	isChangePosition = false;
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
FinalStageUI::~FinalStageUI()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void FinalStageUI::UpdateGameObject(float _deltaTime)
{
	if (playerObject->GetClearFlag())
	{
		++clearCount;

		if (!isChangePosition)
		{
			firstCollectionUI->SetDrawPosition(Vector3(-150.0f, -200.0f, 0.0f));
			firstCollectionUI->ResetDraw();

			secondCollectionUI->SetDrawPosition(Vector3(0.0f, -200.0f, 0.0f));
			secondCollectionUI->ResetDraw();

			thirdCollectionUI->SetDrawPosition(Vector3(150.0f, -200.0f, 0.0f));
			thirdCollectionUI->ResetDraw();
			isChangePosition = true;
		}

		if (clearCount >= 120)
		{
			firstCollectionUI->DrawInGame();
		}

		if (clearCount >= 180)
		{
			secondCollectionUI->DrawInGame();
		}

		if (clearCount >= 240)
		{
			thirdCollectionUI->DrawInGame();
		}
	}
	else
	{
		firstCollectionUI->DrawInGame();
		secondCollectionUI->DrawInGame();
		thirdCollectionUI->DrawInGame();
	}
}
