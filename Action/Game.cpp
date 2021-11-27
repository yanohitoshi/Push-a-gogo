//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Game.h"
#include "SDL.h"
#include <SDL_mixer.h>
#include <glew.h>
#include <algorithm>
#include "FPS.h"
#include "RenderingObjectManager.h"
#include "AudioManager.h"
#include "InputSystem.h"
#include "PhysicsWorld.h"
#include "BaseScene.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "TutorialStageScene.h"
#include "FirstStageScene.h"
#include "SecondStageScene.h"
#include "ThirdStageScene.h"
#include "FourthStageScene.h"
#include "FinalStageScene.h"
#include "ResultScene.h"
#include "GameObject.h"
#include "GeometryInstanceManager.h"

// シーンチェンジを行うかフラグの初期化
bool Game::isChangeScene = false;
// ゲーム全体で見るコンティニューされたかどうかの判定フラグの初期化
bool Game::continueFlag = false;

/*
@brief  コンストラクタ
*/
Game::Game()
	: fps(nullptr)
    , isRunning(true)
	, screenWidth(0)
	, screenHeight(0)
	, isFullScreen(true)
	, FullScreenWidth(1920)
	, FullScreenHeight(1080)
	, WindowScreenWidth(1080)
	, WindowScreenHeight(800)
{
}

/*
@brief  デストラクタ
*/
Game::~Game()
{
}

/*
@brief  初期化処理
@return true : 成功 , false : 失敗
*/
bool Game::Initialize()
{
	//SDLの初期化
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

    //入力管理クラスの初期化
	inputSystem = new InputSystem();
	// 初期化と成功したか失敗したかのチェック
	if (!inputSystem->Initialize())
	{
		SDL_Log("Failed to initialize input system");
		return false;
	}

	// フルスクリーンかどうかを判定	
	if (isFullScreen == true) // フルスクリーンの場合
	{
		// スクリーンサイズをフルスクリーンに初期化
		screenWidth = FullScreenWidth;
		screenHeight = FullScreenHeight;
	}
	else if (isFullScreen == false) // フルスクリーンでない場合
	{
		// スクリーンサイズを任意のウィンドウサイズに初期化
		screenWidth = WindowScreenWidth;
		screenHeight = WindowScreenHeight;

	}

	//レンダラーの初期化
	RenderingObjectManager::CreateInstance();

	//画面作成
	// 初期化と成功したか失敗したかのチェック
	if (!RENDERING_OBJECT_MANAGER->Initialize(screenWidth, screenHeight, isFullScreen))
	{
		SDL_Log("Failed to initialize renderer");
		RenderingObjectManager::DeleteInstance();
		return false;
	}

	// ※サウンド系統未実装
	// オーディオ管理クラスの生成
	AudioManager::CreateInstance();

	// サウンドの初期化
	if (!Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG))
	{
		return false;
	}

	// SDLMixer API初期化　44100:音源の周波数 2:ステレオ 4096:内部バッファサイズ
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		Mix_CloseAudio();
		Mix_Quit();
		return false;
	}

	int decordNum = Mix_GetNumMusicDecoders();

	for (int i = 0; i < decordNum; ++i)
	{
		printf("MusicDecorder %d : %s\n", i, Mix_GetMusicDecoder(i));
	}

	int chunkNum = Mix_GetNumChunkDecoders();

	for (int i = 0; i < chunkNum; ++i)
	{
		printf("SoundDecorder %d : %s\n", i, Mix_GetChunkDecoder(i));
	}

    //当たり判定用クラスの初期化
	PhysicsWorld::CreateInstance();

	//FPS管理クラスの初期化
	fps = new FPS();

	// ビュー行列を生成してRendererに渡す
	Matrix4 v = Matrix4::CreateLookAt(Vector3(-800.0f, 0.0f, -200.0f), Vector3(200.0f, 0.0f, 0.0f), Vector3::UnitZ);
	RENDERING_OBJECT_MANAGER->SetViewMatrix(v);

	// 最初のシーンステータスの初期化
	nowSceneState = TITLE_SCENE;
	// 最初のシーンを生成
	nowScene = new TitleScene();

	//// 最初のシーンステータスの初期化
	//nowSceneState = STAGE_SELECT_SCENE;
	//// 最初のシーンを生成
	//nowScene = new StageSelectScene();

	// 現在のシーンのステータスをレンダラーに渡す
	RENDERING_OBJECT_MANAGER->SetNowSceneState(nowSceneState);

	return true;
}

/*
@brief  終了処理
*/
void Game::Termination()
{
	// 今のシーンを解放
	delete nowScene;
    //データのアンロード
	UnloadData();
    //スタティッククラスの解放処理
	RenderingObjectManager::DeleteInstance();
	PhysicsWorld::DeleteInstance();
    //クラスの解放処理
    delete fps;
    delete inputSystem;
    //サブシステムの終了
	SDL_Quit();
}

/*
@brief  ゲームループ
*/
void Game::GameLoop()
{
	// isRunningがtrueの間ループ
	while (isRunning)
	{
		// 入力更新
		ProcessInput();
		// ゲームのアップデート
		UpdateGame();
		// 描画更新
		GenerateOutput();
		// デルタタイムの更新
		fps->Update();
		// シーン遷移が行われる場合
		if (isChangeScene == true)
		{
			// シーンの変更
			ChangeScene(nowSceneState, nowScene);
		}
	}
}


/*
@brief   ロードしたデータの解放
*/
void Game::UnloadData()
{
	// Rendererがnullptrじゃなかったら
	if (RENDERING_OBJECT_MANAGER != nullptr)
	{
		// データをアンロード
		RENDERING_OBJECT_MANAGER->UnloadData();
		// Rendererの後片付けを行う
		RENDERING_OBJECT_MANAGER->Shutdown();
	}
}

/*
@brief  入力関連の処理
*/
void Game::ProcessInput()
{
	// inputSystemのUpdateの準備をする（SDL_PollEventsの直前に呼ぶ）
	inputSystem->PrepareForUpdate();

	// SDL_EVENTの生成
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEWHEEL:
			inputSystem->ProcessEvent(event);
			break;
		default:
			break;
		}
	}

	// 入力状態のアップデート
	inputSystem->Update();

	// 入力状態を保存
	const InputState& state = inputSystem->GetState();

	// 当たり判定を可視化させるデバッグモードの切り替え
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_0) == Released)
	{
		PHYSICS->ToggleDebugMode();
	}

	// エスケープまたはコントローラーのバックボタンが押されたらゲームループから抜ける
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == Released ||
		state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_BACK) == Pressed)
	{
		isRunning = false;
	}

	// 次のシーンのステータス状態保存用変数生成
	SceneState tmpSceneState;

	// シーンのアップデート
	tmpSceneState = nowScene->Update(state);

	// もしシーン遷移が行われない場合オブジェクトに入力状態を渡して更新
	if (isChangeScene == false && Game::GetContinueFlag() == false)
	{
		ProcessInputs(state);
	}

	// 今のシーンと次のシーンが違うまたはコンテニューが選択されたら
	if (tmpSceneState != nowSceneState || Game::GetContinueFlag())
	{
		// 今のシーンステータスに次のシーンステータスを入れる
		nowSceneState = tmpSceneState;

		// シーン変更フラグをtrueに
		isChangeScene = true;
	}
}

/*
@fn シーン変更関数
@brief 前のシーンの解放と次のシーンの生成を行う
@param _state シーンの状態
@param _scene 進行中のシーンのポインタ
*/
void Game::ChangeScene(SceneState _state, BaseScene* _scene)
{

	// シーン変更があった際に全ての使用済みオブジェクトを削除
	GameObject::RemoveUsedGameObject();
	// シーンのメモリをdelete
	delete _scene;

	RENDERING_OBJECT_MANAGER->GetGeometryInstanceManager()->ClearGeometryInstanceGameObjectMap();
	// シーン遷移判定に使用するフラグを初期化
	isChangeScene = false;
	continueFlag = false;

	// _stateを参照して必要なシーンを生成
	switch (_state)
	{
	case SceneState::TITLE_SCENE:
		nowScene = new TitleScene();
		break;
	case SceneState::TUTORIAL_SATGE_SCENE:
		nowScene = new TutorialStageScene();
		break;
	case SceneState::STAGE_SELECT_SCENE:
		nowScene = new StageSelectScene();
		break;
	case SceneState::FIRST_SATGE_SCENE:
		nowScene = new FirstStageScene();
		break;
	case SceneState::SECOND_SATGE_SCENE:
		nowScene = new SecondStageScene();
		break;
	case SceneState::THIRD_SATGE_SCENE:
		nowScene = new ThirdStageScene();
		break;
	case SceneState::FOURTH_SATGE_SCENE:
		nowScene = new FourthStageScene();
		break;
	case SceneState::FINAL_STAGE_SCENE:
		nowScene = new FinalStageScene();
		break;
	case SceneState::RESULT_SCENE:
		nowScene = new ResultScene();
		break;
	}

	RENDERING_OBJECT_MANAGER->SetNowSceneState(nowSceneState);
}

/*
@brief  描画関連の処理
*/
void Game::GenerateOutput()
{
	// 描画処理
	RENDERING_OBJECT_MANAGER->Draw();
}

/*
@brief  ゲームのアップデート処理
*/
void Game::UpdateGame()
{
	// デルタタイムの更新
	float deltaTime = fps->GetDeltaTime();

	// GameObjectsの更新処理へ
	UpdateGameObjects(deltaTime);
}

/*
@brief  ゲームオブジェクトのアップデート処理
@param	最後のフレームを完了するのに要した時間
*/
void UpdateGameObjects(float _deltaTime)
{
	// オブジェクトの更新フラグをtrueに
	GameObject::updatingGameObject = true;
	
	// gameObjectMap内に存在する全てのオブジェクトを更新
	for (auto itr = GameObject::gameObjectMap.begin(); itr != GameObject::gameObjectMap.end(); ++itr)
	{
		for (auto gameObject : itr->second)
		{
			// objectの更新処理呼び出し
			gameObject->Update(_deltaTime);
		}
	}

	// 途中追加されたobjectの更新処理
	// ※ループ中でgameObjectMapに合流させてしまうと添え字がずれて例外をスローしてしまうので一度別のvector内で更新してその後合流させる
	for (auto pending : GameObject::pendingGameObjects)
	{
		// 更新処理
		// WorldTransformを更新
		pending->ComputeWorldTransform();

		// マップに追加
		// 追加されるオブジェクトと同じ種類のオブジェクト可変長コンテナがすでにあるかどうかTagを用いて判定
		auto gameObjects = GameObject::gameObjectMap.find(pending->GetTag());
		if (gameObjects != GameObject::gameObjectMap.end())
		{
			gameObjects->second.emplace_back(pending);
		}
		else  
		{
			std::vector<GameObject*> tmpVector;
			tmpVector.emplace_back(pending);
			GameObject::gameObjectMap[pending->GetTag()] = tmpVector;
		}

		// 使用済み配列をクリア
		GameObject::pendingGameObjects.clear();
	}

	// 更新フラグをfalseに
	GameObject::updatingGameObject = false;

	// 死亡状態のオブジェクト用vectorを作成
	std::vector<class GameObject*>deadObjects;

	// gameObjectMapから死んでいるオブジェクトを探して死亡状態のオブジェクト用vectorに追加
	for (auto itr = GameObject::gameObjectMap.begin(); itr != GameObject::gameObjectMap.end(); ++itr)
	{
		for (auto gameObject : itr->second)
		{
			// ステータスがDeadだったら
			if (gameObject->GetState() == State::Dead )
			{
				// Dead状態オブジェクト用可変長コンテナに格納
				deadObjects.emplace_back(gameObject);
			}
		}
	}

	// 探し終わったらdeadObjects内のオブジェクトを削除
	while (!deadObjects.empty())
	{
		// 削除
		deadObjects.pop_back();
	}

	// 死亡状態のオブジェクト用配列をクリア
	deadObjects.clear();
}

/*
@brief  ゲームオブジェクトの入力処理
@param	_keyState 入力情報
*/
void ProcessInputs(const InputState& _state)
{
	// オブジェクトの更新フラグをtrueに
	GameObject::updatingGameObject = true;

	// 生存しているオブジェクトの入力状態を更新
	for (auto itr = GameObject::gameObjectMap.begin(); itr != GameObject::gameObjectMap.end(); ++itr)
	{
		for (auto gameObject : itr->second)
		{
			// objectの入力処理呼び出し
			gameObject->ProcessInput(_state);
		}
	}
	
	// 更新フラグをfalseに
	GameObject::updatingGameObject = false;

}