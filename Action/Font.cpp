//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Font.h"
#include "Texture.h"
#include <vector>
#include "Game.h"
#include "RenderingObjectManager.h"

/*
@fn コンストラクタ
@brief Fontクラスの生成を行う
*/
Font::Font()
{
}

/*
@fn デストラクタ
@brief Fontクラスの削除を行う
*/
Font::~Font()
{
}

/*
@fn ファイルロード関数
@brief TTFファイルのロードを行う
@param fileName ロードするファイルのパス
*/
bool Font::Load(const std::string& fileName)
{
	// サポートされているフォントサイズ
	std::vector<int> fontSizes = {
		8, 9,
		10, 11, 12, 14, 16, 18,
		20, 22, 24, 26, 28,
		30, 32, 34, 36, 38,
		40, 42, 44, 46, 48,
		52, 56,
		60, 64, 68,
		72
	};

	for (auto& size : fontSizes)
	{
		TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);
		if (font == nullptr)
		{
			SDL_Log("Failed to load font %s in size %d", fileName.c_str(), size);
			return false;
		}
		fontData.emplace(size, font);
	}
	return true;
}

/*
@fn アンロード関数
@brief TTFファイルのアンロードを行う
*/
void Font::Unload()
{
	for (auto& font : fontData)
	{
		TTF_CloseFont(font.second);
	}
}

/*
@fn texture生成関数
@brief フォントを使用したtextureの生成を行う
@param renderingText 生成するtextureに使用する文字列
@param color 指定する色（デフォルトは白）
@param pointSize フォントのサイズ（デフォルトは30）
*/
Texture* Font::RenderText(const std::string& renderingText,const Vector3& color,int pointSize)
{
	//return nullptr;
	Texture* texture = nullptr;

	// SDL_Colorを変換
	SDL_Color sdlColor;
	sdlColor.r = static_cast<Uint8>(color.x * 255);
	sdlColor.g = static_cast<Uint8>(color.y * 255);
	sdlColor.b = static_cast<Uint8>(color.z * 255);
	sdlColor.a = 255;

	// フォントデータからポイントサイズを探す
	auto iter = fontData.find(pointSize);
	if (iter != fontData.end())
	{
		TTF_Font* font = iter->second;
		const std::string& actualText = renderingText;

		SDL_Surface* surf = TTF_RenderUTF8_Blended(font, actualText.c_str(), sdlColor);
		if (surf != nullptr)
		{
			// サーフェスからテクスチャに変換する
			texture = new Texture();
			texture->CreateFromSurface(surf);
			SDL_FreeSurface(surf);
		}
	}
	else
	{
		SDL_Log("Point size %d is unsupported", pointSize);
	}

	return texture;
}

