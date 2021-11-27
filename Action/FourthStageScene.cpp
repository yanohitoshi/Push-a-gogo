#include "FourthStageScene.h"
#include "RenderingObjectManager.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "ForthStageCreator.h"
#include "ForthStageUI.h"
#include "CountDownFont.h"
#include "CollectionObject.h"

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
	endFlag = false;
	lightDownFlag = true;
	state = SceneState::FOURTH_SATGE_SCENE;

	// クリエイター生成
	ForthStageCreator* fifthStageCreator = new ForthStageCreator(false, Tag::OTHER);

	//ステージ情報ファイルを開く
	if (!fifthStageCreator->OpenFile())
	{
		//プレイヤーの生成
		playerObject = fifthStageCreator->CreatePlayer();
		//ステージを生成する
		fifthStageCreator->CreateStage();
	}

	CollectionObject* firstCollection = fifthStageCreator->FindCollectionObject(CollectionTag::FIRST);
	CollectionObject* secondCollection = fifthStageCreator->FindCollectionObject(CollectionTag::SECOND);
	CollectionObject* thirdCollection = fifthStageCreator->FindCollectionObject(CollectionTag::THIRD);

	//シーンUIを追加
	new ForthStageUI(playerObject, firstCollection, secondCollection, thirdCollection);
}

FourthStageScene::~FourthStageScene()
{
}

SceneState FourthStageScene::Update(const InputState& _inputState)
{
	// シーンが始まったらライトを強くする
	if (startScene == true)
	{
		// シーン開始時のライトアップ処理
		StartSceneLightUpProcess();
	}

	// クリアしたかのチェックとクリアカウントを数える処理関数
	SceneClearCountProcess(playerObject);

	// クリアカウントが一定を超えたらシーンを切り替える
	if (clearCount >= ClearToChangeSceneTime)
	{
		state = SceneState::FINAL_STAGE_SCENE;
	}

	// タイムオーバー状態かつライトを一定まで落とす状態だったら
	if (CountDownFont::GetTimeOverFlag() == true && lightDownFlag == true)
	{
		// コンティニュー選択処理
		ContinueSelectProcess(_inputState);
	}

	// コンテニューかゲームオーバーが選択されたら
	if (isContinueFlag == true || endFlag == true)
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
