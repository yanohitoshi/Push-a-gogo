#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class MusicComponent;
class SoundEffectComponent;

/*
@file FinalSceneSoundManager.h
@brief 最終ステージシーンのサウンドを管理するクラス
*/
class FinalSceneSoundManager :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param 親クラスのシーンクラスのポインタ
	*/
	FinalSceneSoundManager(BaseScene* _owner);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~FinalSceneSoundManager()override;

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// オーナークラスのポインタ
	BaseScene* owner;

	// BGMを管理するクラス
	MusicComponent* bgm;
	// ゲームオーバーBGM
	MusicComponent* gameOverBgm;
	// カウントダウンサウンドエフェクト
	SoundEffectComponent* countDown;
	// コンティニューサウンドエフェクト
	SoundEffectComponent* continueSound;
	// ゲーム終了サウンドエフェクト
	SoundEffectComponent* gameEnd;

	// カウントダウン音を鳴らすかどうか
	bool isCountDownPlay;
	// BGMが切り替えられたかどうか
	bool isbgmChanged;

	// コンティニューサウンドエフェクトを再生するかどうか
	bool isPlayContinue;
	// ゲーム終了サウンドエフェクトを再生するかどうか
	bool isPlayGameEnd;
};

