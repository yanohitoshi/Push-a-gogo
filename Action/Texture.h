﻿#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include <string>
#include <vector>

/*
@file Texture.h
@brief Textureを生成する
*/
class Texture
{
public:

	/*
	@brief	コンストラクタ
	*/
    Texture();

	/*
	@brief	デストラクタ
	*/
    ~Texture();
	/*
	@brief	テクスチャのロード
	@param	_fileName テクスチャのファイル名
	@return	true : 成功 , false : 失敗
	*/
	bool Load(const std::string& _fileName);
	
	/*
	@brief	ロードしたテクスチャの解放
	*/
	void Unload();

	/*
	@brief	Surfaceを元にtextureを作成
	@param	_surface 元にするSurfaceクラスのポインタ
	*/
	void CreateFromSurface(struct SDL_Surface* _surface);

	/*
	@brief	レンダリング用のテクスチャを作成
	@param	テクスチャの横幅
	@param	テクスチャの縦幅
	@param	ピクセルデータのフォーマット
	*/
	void CreateForRendering(int _width, int height, unsigned int _format);

	/*
	@brief	テクスチャをアクティブにする
	*/
	void SetActive();

	static bool LoadDiv(
		 const std::string& _fileName,const unsigned int _allNum
		,const unsigned int _widthNum, const unsigned int _heightNum
		,const unsigned int _width, const unsigned int _height
		,std::vector<Texture*> textures);

	/*
	@brief	キューブマップの読み込み
	@param	ロードするファイルのパス
	*/
	bool LoadCubeMap(const std::string& in_filePath);

private:

	// テクスチャID
	unsigned int textureID;

	//テクスチャの横幅
	int width;
	//テクスチャの縦幅
	int height;

public://ゲッターセッター

	/*
	@fn widthのgetter関数
	@brief	テクスチャの横幅を取得する
	@return 横幅
	*/
	int GetWidth() const { return width; }

	/*
	@fn heightのgetter関数
	@brief	テクスチャの縦幅を取得する
	@return 縦幅
	*/
	int GetHeight() const { return height; }

	/*
	@fn textureIDのgetter関数
	@brief	テクスチャのIDを取得する
	@return テクスチャのID
	*/
	int GetTextureID() const { return textureID; }
};

