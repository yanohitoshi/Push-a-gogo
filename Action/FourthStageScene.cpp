//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "FourthStageScene.h"
#include "RenderingObjectManager.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "FourthStageCreator.h"
#include "ForthStageUI.h"
#include "CountDownFont.h"
#include "CollectionObject.h"
#include "FourthSceneSoundManager.h"

/*
@fn コンストラクタ
@brief  Sceneの生成を行う
*/
FourthStageScene::FourthStageScene()
{
	// ライト情報初期化
	light = Vector3(0.1f, 0.1f, 0.1f);
	RENDERING_OBJECT_MANAGER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERING_OBJECT_MANAGER->GetDirectionalLight();
	dir.direction = Vector3(0.5f, 0.5f, 0.8f);
	dir.diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// メンバー変数初期化
	clearCount = 0;
	changeCount = 0;
	startScene = true;
	isContinueFlag = false;
	isEndFlag = false;
	lightDownFlag = true;
	state = SceneState::FOURTH_SATGE_SCENE;

	// クリエイター生成
	FourthStageCreator* fourthStageCreator = new FourthStageCreator(false, Tag::OTHER);

	//ステージ情報ファイルを開く
	if (!fourthStageCreator->OpenFile())
	{
		//プレイヤーの生成
		playerObject = fourthStageCreator->CreatePlayer();
		//ステージを生成する
		fourthStageCreator->CreateStage();
	}

	// クリエイターから収集物クラスのポインタをもらう
	CollectionObject* firstCollection = fourthStageCreator->FindCollectionObject(CollectionTag::FIRST);
	CollectionObject* secondCollection = fourthStageCreator->FindCollectionObject(CollectionTag::SECOND);
	CollectionObject* thirdCollection = fourthStageCreator->FindCollectionObject(CollectionTag::THIRD);

	//シーンUIを追加
	new ForthStageUI(playerObject, firstCollection, secondCollection, thirdCollection);

	// クリエイターの状態をdeadにし片づける
	fourthStageCreator->SetState(State::Dead);

	// サウンドマネージャークラスを生成
	new FourthSceneSoundManager(this);
}

/*
@fn デストラクタ
@brief  sceneの削除を行う
*/
FourthStageScene::~FourthStageScene()
{
}

/*
@fn　シーンのアップデート関数
@brief	シーンの更新処理を行う
@param	入力情報
@return シーンの遷移を判定するためのenum型のSceneState
*/
SceneState FourthStageScene::Update(const InputState& _inputState)
{
	// シーンが始まったらライトを強くする
	if (startScene == true)
	{
		// シーン開始時のライトアップ処理
		StartSceneLightUp();
	}

	// クリアしたかのチェックとクリアカウントを数える処理関数
	SceneClearCount(playerObject);

	// クリアカウントが一定を超えたらシーンを切り替える
	if (clearCount >= ClearToChangeSceneTime)
	{
		state = SceneState::FINAL_STAGE_SCENE;
	}

	// タイムオーバー状態かつライトを一定まで落とす状態だったら
	if (CountDownFont::GetTimeOverFlag() == true && lightDownFlag == true)
	{
		// コンティニュー選択処理
		ContinueSelect(_inputState);
	}

	// コンテニューかゲームオーバーが選択されたら
	if (isContinueFlag == true || isEndFlag == true)
	{
		// コンティニュー選択時のライト遷移処理
		LightTransitionAtContinue();
	}

	// コンティニュー選択後のシーン切り替えカウントが一定以上になったら
	if (changeCount >= ContinueToChangeScene)
	{
		// シーンステータス切り替え処理
		SceneStateChangeAtContinue(SceneState::FOURTH_SATGE_SCENE);
	}

	// 一定時間操作がなかったらタイトルへ
	if (playerObject->GetRestartFlag() == true)
	{
		state = SceneState::TITLE_SCENE;
	}

	// 更新後のシーンステータスを返す
	return state;
}
