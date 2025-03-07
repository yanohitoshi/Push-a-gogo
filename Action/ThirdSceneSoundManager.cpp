//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ThirdSceneSoundManager.h"
#include "AudioResourceManager.h"
#include "MusicComponent.h"
#include "SoundEffectComponent.h"
#include "BaseScene.h"

/*
@fn コンストラクタ
@param 親クラスのシーンクラスのポインタ
*/
ThirdSceneSoundManager::ThirdSceneSoundManager(BaseScene* _owner)
	: GameObject(false, Tag::AUDIO)
{
	// 変数初期化
	owner = _owner;
	isCountDownPlay = true;
	isbgmChanged = false;
	isPlayContinue = true;
	isPlayGameEnd = true;

	// BGMを生成
	bgm = new MusicComponent(this, "Assets/Sound/Bgm/Game/Third.wav");
	gameOverBgm = new MusicComponent(this, "Assets/Sound/Bgm/TimeUp/TimeUp.wav");

	// サウンドエフェクトを生成
	continueSound = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/Continue/Continue.wav");
	gameEnd = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/GameOver/GameEnd.wav");
	countDown = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/CountDown/CountDown.wav");

}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
ThirdSceneSoundManager::~ThirdSceneSoundManager()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void ThirdSceneSoundManager::UpdateGameObject(float _deltaTime)
{
	// カウントダウン音を再生する状態だったら
	if (!owner->GetStartScene() && isCountDownPlay)
	{
		// カウントダウン音を再生する
		countDown->Play();
		// カウントダウン音を再生するかをfalseに切り替える
		isCountDownPlay = false;
	}

	// ゲームBGMを再生するかを判定
	bool isPlayBgm = !isCountDownPlay && !owner->GetIsSceneClear() && !owner->GetIsTimeOver();

	// 再生する状態かつ再生されて居なかったら
	if (isPlayBgm && !bgm->IsPlaying())
	{
		// ゲームBGM再生する
		bgm->Play();
	}

	// シーンをクリアしたら
	if (owner->GetIsSceneClear())
	{
		// ゲームBGM停止する
		bgm->Stop();
	}

	// タイムオーバーになってBGMが切り替わっていなかったら
	if (owner->GetIsTimeOver() && !isbgmChanged)
	{
		// 再生されていたら
		if (bgm->IsPlaying())
		{
			// ゲームBGMを停止
			bgm->Stop();
		}

		// ゲームオーバーBGMを再生
		gameOverBgm->Play();
		// 切り替えフラグをfalseにする
		isbgmChanged = true;
	}

	// コンティニューが選択されていたら
	if (owner->GetIsContinueFlag() && isPlayContinue)
	{
		// コンティニューサウンドエフェクトを再生
		continueSound->Play();
		isPlayContinue = false;
	}

	// ゲーム終了が選択されていたら
	if (owner->GetIsEndFlag() && isPlayGameEnd)
	{
		gameEnd->Play();
		isPlayGameEnd = false;
	}
}