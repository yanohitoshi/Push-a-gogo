//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "StageSelectSprite.h"
#include "SpriteComponent.h"
#include "StageSelectSceneUI.h"
#include "GraphicsResourceManager.h"

/*
@fn コンストラクタ
@parma 親クラスのポインタ
@parma シーンのステータス
@parma 描画する画像のファイルネーム
*/
StageSelectSprite::StageSelectSprite(StageSelectSceneUI* _owner, SceneState _state,const std::string& _spriteFileName)
	: GameObject(false, Tag::UI)
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, 100.0f, 0.0f));
	SetScale(Vector3(1.0f, 1.0f, 1.0f));

	myState = _state;
	_owner->AddStageSelectSpriteMap(this, myState);
	isVisible = true;

	// spriteComponenをnewする
	sprite = new SpriteComponent(this, false);
	// 背景テクスチャをロード
	Texture* tex = GRAPHICS_RESOURCE->CreateTexture(_spriteFileName);
	// 背景テクスチャをセット
	sprite->SetTexture(tex);
	// 映す映さないをセット
	sprite->SetVisible(isVisible);
	// alpha値をセット
	sprite->SetAlpha(1.0f);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
StageSelectSprite::~StageSelectSprite()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void StageSelectSprite::UpdateGameObject(float _deltaTime)
{
	// 映す映さないをセット
	sprite->SetVisible(isVisible);
}