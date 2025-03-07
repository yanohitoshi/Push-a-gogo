#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Component.h"
#include "Math.h"

/*
 @file ParticleComponent.h
 @brief 画像を管理しそれを3D空間上に描画するクラス。
*/
class ParticleComponent :
	public Component
{
public:

	//パーティクルに対するブレンドの種類
	typedef enum PARTICLE_BLEND_ENUM
	{
		PARTICLE_BLEND_ENUM_ALPHA,
		PARTICLE_BLEND_ENUM_ADD,
		PARTICLE_BLEND_ENUM_MULT
	}PARTICLE_ENUM;

	/*
	@fn コンストラクタ
	@param _owner 親クラスのポインタ
	@param _useStaticBillboardMat ビルボード行列を使用するかどうか
	@param _offset 親オブジェクトクラスと画像を描画する位置の差
	@param _scale 画像の描画サイズ
	@param _updateOrder 描画順を入れ替える際に用いる数値
	*/
	ParticleComponent(GameObject* _owner, bool _useStaticBillboardMat ,const Vector3& _offset = Vector3(1, 1, 1), float _scale = 1.0f, int _updateOrder = 100);
	
	/*
	@fn デストラクタ
	@brief  Componentの削除を行う
	*/
	~ParticleComponent();

	virtual void Update(float _deltaTime) override {};

	/*
	@brief　描画処理
	@param	_shader 使用するシェーダークラスのポインタ
	*/
	void Draw(class Shader* _shader);

	// カメラ距離でのソート用
	bool operator < (const ParticleComponent& rhs) const;
	bool operator > (const ParticleComponent& rhs) const;

private:

	// 親クラスのポインタ
	GameObject* owner;
	//親オブジェクトクラスと画像を描画する位置の差
	Vector3 offset;
	//画像に乗算する色
	Vector3 color;
	//サイズ
	float scale;
	//透明度
	float alpha; 
	//テクスチャID
	int textureID; 
	//ブレンドタイプ
	PARTICLE_ENUM blendType;
	//描画を行うか
	bool visible;
	// BillboardMatを使用するか
	bool useStaticBillboardMat;
	// ビルボード行列
	static Matrix4 staticBillboardMat; 
	// カメラのワールド座標
	static Vector3 staticCameraWorldPos;
	//描画順(数字が少ないものから描画される)
	int drawOrder;
	//反転を行うか
	bool reverce;

public: //ゲッターセッター

	/*
	@return テクスチャID
	*/
	int GetTextureID() const { return textureID; }

	/*
	@param _texId テクスチャID
	*/
	void SetTextureID(int _texId) { textureID = _texId; }

	/*
	@return ブレンドタイプ
	*/
	PARTICLE_ENUM GetBlendType() const { return blendType; }

	/*
	@param _color 画像に乗算する色
	*/
	void SetColor(const Vector3& _color) { color = _color; }

	/*
	@param _alfa 透明度0~1
	*/
	void SetAlpha(float _alpha) { alpha = _alpha; }

	/*
	@param サイズ
	*/
	void SetScale(float _scale) { scale = _scale; }

	/*
	@param _mat ビルボード行列
	*/
	void SetBillboardMat(const Matrix4& _mat) {	staticBillboardMat = _mat;	}

	/*
	@param _brendType カメラのワールド座標
	*/
	void SetBlendMode(PARTICLE_ENUM _blendType){blendType = _blendType;	}
	
	/*
	@brief　描画をするかどうかを設定
	@param	true : 描画する , false : 描画しない
	*/
	void SetVisible(bool _visible) { visible = _visible; }

	/*
	@brief　描画をするかどうかを取得する
	@return	true : 描画する , false : 描画しない
	*/
	bool GetVisible() const { return visible; }

	/*
	@fn 描画順をセット
	@param _drawOrder 描画順
	*/
	void SetDrawOrder(int _drawOrder) { drawOrder = _drawOrder; }

	/*
	@fn 描画順のgetter
	@return 描画順
	*/
	int GetDrawOrder() const { return drawOrder; }

	/*
	@fn 親オブジェクトの座標と描画位置の差をセット
	@param _offset 親オブジェクトの座標と描画位置の差
	*/
	void SetOffSet(Vector3 _offset) { offset = _offset; };

	/*
	@param _flag 反転を行うか
	*/
	void SetReverce(bool _flag) { reverce = _flag; }
};

/*
@return ビルボード行列(Matrix4)
*/
Matrix4 GetBillboardMatrix();