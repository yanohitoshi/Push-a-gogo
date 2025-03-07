//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "CountDownFont.h"
#include "GraphicsResourceManager.h"
#include "TimeSprite.h"
#include "SpriteComponent.h"
#include "CountDownBackFont.h"
#include "WarningSprite.h"
#include "PlayerObject.h"

// 静的メンバーの初期化
bool CountDownFont::timeOverFlag = false;
bool CountDownFont::countStartFlag = false;

/*
@brief	コンストラクタ
@param	カウントする時間
*/
CountDownFont::CountDownFont(PlayerObject* _playerObject,int _time)
	: GameObject(false,Tag::UI)
	, AddTimeCount(60)
	, ChangeColorCount(30)
{
	// メンバー変数の初期化
	SetPosition(Vector3(700.0f, 480.0f, 0.0f));
	time = _time;
	warningFlag = false;
	// SpriteComponentの初期化
	sprite = new SpriteComponent(this,false,110);
	sprite->SetAlpha(1.0f);
	playerObject = _playerObject;
	isCountDown = false;
	// カウントダウンフォントの影を作るためのバックフォントを生成
	new CountDownBackFont(this,_time);
	// 時間表示textureクラスを生成
	new TimeSprite();

	new WarningSprite(this);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
CountDownFont::~CountDownFont()
{
	// 静的メンバーの初期化
	timeOverFlag = false;
	countStartFlag = false;
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void CountDownFont::UpdateGameObject(float _deltaTime)
{
	isCountDown = countStartFlag == true && !playerObject->GetClearFlag();

	// ゲームスタートしたらカウント開始
	if (isCountDown)
	{
		// フレームカウントを数える
		frameCount++;
		// カウントが60になったら
		if (frameCount >= AddTimeCount)
		{
			// timeを減らす
			time -= 1;
			frameCount = 0;
		}
	}

	// 30以上の時は白色で描画
	if (time > ChangeColorCount)
	{
		sprite->SetTexture(GRAPHICS_RESOURCE->GetTimeTexture(time - 1));
	}
	else if (time <= ChangeColorCount && time >= 1)	// 30以下の時は白色で描画
	{
		// 警告フラグをtrueに
		warningFlag = true;
		sprite->SetTexture(GRAPHICS_RESOURCE->GetTimeRedTexture(time - 1));
	}

	// textureを先に作ってvector配列に格納している都合上0を描画するときnullにアクセスしてしまうのを回避
	if (time == 0)
	{
		sprite->SetTexture(GRAPHICS_RESOURCE->GetTimeRedTexture(-1));
	}

	// timeが-1以下になったらタイムオーバーにする
	if (time <= -1)
	{
		timeOverFlag = true;
		sprite->SetVisible(false);
	}
}