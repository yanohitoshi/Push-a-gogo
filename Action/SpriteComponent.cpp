//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "SpriteComponent.h"
#include "Texture.h"
#include "Shader.h"
#include "GameObject.h"
#include "Game.h"
#include "RenderingObjectManager.h"

/*
@fn コンストラクタ
@param _owner 親となるGameObjectのポインタ
@param _isBackGround 背景画像かどうかのフラグ(bool)
@param _drawOrder 描画順を決める値(int)
*/
SpriteComponent::SpriteComponent(GameObject * _owner, bool _isBackGround,int _drawOrder)
    :Component(_owner)
    , texture(nullptr)
    , drawOrder(_drawOrder)
    , textureWidth(0)
    , textureHeight(0)
	, visible(true)
	, isBackGround(_isBackGround)
	, scale(1.0f)
{

		//レンダラーにポインターを送る
	RENDERING_OBJECT_MANAGER->AddSprite(this);
}

/*
@fn デストラクタ
@brief  Componentの削除を行う
*/
SpriteComponent::~SpriteComponent()
{
	//レンダラーからポインタを削除する
	RENDERING_OBJECT_MANAGER->RemoveSprite(this);
}

/*
@brief	描画処理
@param _shader 使用するシェーダークラスのポインタ
*/
void SpriteComponent::Draw(Shader * _shader)
{
	//画像情報が空でないか、親オブジェクトが未更新状態でないか
	if (texture&&owner->GetState()!=State::Dead)
	{
		Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(textureWidth * scale),
			static_cast<float>(textureHeight * scale),
			1.0f);

		Matrix4 world = scaleMatrix * owner->GetWorldTransform();

		_shader->SetMatrixUniform("uWorldTransform",world);
		_shader->SetFloatUniform("uAlpha", alpha);

		texture->SetActive();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		
	}
}

/*
@fn テクスチャをセットし縦横の長さを計算する
@param _texture 使用するテクスチャのポインタ
*/
void SpriteComponent::SetTexture(Texture * _texture)
{
	if (_texture == nullptr)
	{
		return;
	}
	texture = _texture;
	textureWidth = texture->GetWidth();
	textureHeight = texture->GetHeight();
}