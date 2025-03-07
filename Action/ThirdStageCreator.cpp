//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ThirdStageCreator.h"
#include "PlayerObject.h"
#include "GroundObject.h"
#include "BreakBlockObject.h"
#include "LightObject.h"
#include "MoveBlockObject.h"
#include "MoveWallBlock.h"
#include "PushBoxObject.h"
#include "SwitchBaseObject.h"
#include "JumpSwitchObject.h"
#include "ExplosionObject.h"
#include "NeedlePanelObject.h"
#include "RespawnPoint.h"
#include "TrackingEnemyObject.h"
#include "NormalEnemyObject.h"
#include "MoveEnemyObject.h"
#include "CameraChangePoint.h"
#include "NextSceneObject.h"
#include "CollectionObject.h"


/*
@fn コンストラクタ
@brief  objectの生成を行う
@param	_reUseGameObject 再利用するかどうかフラグ
@param	_objectTag オブジェクト判別用Tag
*/
ThirdStageCreator::ThirdStageCreator(bool _reUseGameObject, const Tag _objectTag)
	: StageCreatorBase(_reUseGameObject, _objectTag)
	, MaxLayerNumber(17)
	, LightPointPositionZ(7000.0f)
{
}

/*
@fn デストラクタ
@brief マップデータの削除を行う
*/
ThirdStageCreator::~ThirdStageCreator()
{
	//マップデータの削除
	layer1StageData.clear();
	layer2StageData.clear();
	layer3StageData.clear();
	layer4StageData.clear();
	layer5StageData.clear();
	layer6StageData.clear();
	layer7StageData.clear();
	layer8StageData.clear();
	layer9StageData.clear();
	layer10StageData.clear();
	layer11StageData.clear();
	layer12StageData.clear();
	layer13StageData.clear();
	layer14StageData.clear();
	layer15StageData.clear();
	layer16StageData.clear();
	layer17StageData.clear();
	layer18StageData.clear();

	cameraDirectingData.clear();
	//プレイヤーのマップデータ削除
	playerData.clear();

}

/*
@fn ファイルを開く
@return 成功か否か
*/
bool ThirdStageCreator::OpenFile()
{
	// ステージデータ読み込み (baseLayer)
	if (!readTiledJson(layer1StageData, "Assets/Config/StageData/ThirdStageMap.json", "layer1"))
	{
		printf("do'nt have Layer/layer1\n");
		return true;
	}

	// データ配列のサイズXとYを保存
	sizeX = layer1StageData[0].size();
	sizeY = layer1StageData.size();

	// ステージデータ読み込み (layer2) 
	if (!readTiledJson(layer2StageData, "Assets/Config/StageData/ThirdStageMap.json", "layer2"))
	{
		printf("do'nt have Layer/layer2\n");
		return true;
	}
	// ステージデータ読み込み (layer3) 
	if (!readTiledJson(layer3StageData, "Assets/Config/StageData/ThirdStageMap.json", "layer3"))
	{
		printf("do'nt have Layer/layer3\n");
		return true;
	}
	// ステージデータ読み込み (layer4) 
	if (!readTiledJson(layer4StageData, "Assets/Config/StageData/ThirdStageMap.json", "layer4"))
	{
		printf("do'nt have Layer/layer4\n");
		return true;
	}
	// ステージデータ読み込み (layer5) 
	if (!readTiledJson(layer5StageData, "Assets/Config/StageData/ThirdStageMap.json", "layer5"))
	{
		printf("do'nt have Layer/layer5\n");
		return true;
	}

	// ステージデータ読み込み (layer6) 
	if (!readTiledJson(layer6StageData, "Assets/Config/StageData/ThirdStageMap.json", "layer6"))
	{
		printf("do'nt have Layer/layer6\n");
		return true;
	}
	// ステージデータ読み込み (layer7) 
	if (!readTiledJson(layer7StageData, "Assets/Config/StageData/ThirdStageMap.json", "layer7"))
	{
		printf("do'nt have Layer/layer7\n");
		return true;
	}
	// ステージデータ読み込み (layer8) 
	if (!readTiledJson(layer8StageData, "Assets/Config/StageData/ThirdStageMap.json", "layer8"))
	{
		printf("do'nt have Layer/layer8\n");
		return true;
	}
	// ステージデータ読み込み (layer9) 
	if (!readTiledJson(layer9StageData, "Assets/Config/StageData/ThirdStageMap.json", "layer9"))
	{
		printf("do'nt have Layer/layer9\n");
		return true;
	}
	// ステージデータ読み込み (layer10) 
	if (!readTiledJson(layer10StageData, "Assets/Config/StageData/ThirdStageMap.json", "layer10"))
	{
		printf("do'nt have Layer/layer10\n");
		return true;
	}
	// ステージデータ読み込み (layer11) 
	if (!readTiledJson(layer11StageData, "Assets/Config/StageData/ThirdStageMap.json", "layer11"))
	{
		printf("do'nt have Layer/layer11\n");
		return true;
	}
	// ステージデータ読み込み (layer12) 
	if (!readTiledJson(layer12StageData, "Assets/Config/StageData/ThirdStageMap.json", "layer12"))
	{
		printf("do'nt have Layer/layer12\n");
		return true;
	}
	// ステージデータ読み込み (layer13) 
	if (!readTiledJson(layer13StageData, "Assets/Config/StageData/ThirdStageMap.json", "layer13"))
	{
		printf("do'nt have Layer/layer13\n");
		return true;
	}
	// ステージデータ読み込み (layer14) 
	if (!readTiledJson(layer14StageData, "Assets/Config/StageData/ThirdStageMap.json", "layer14"))
	{
		printf("do'nt have Layer/layer14\n");
		return true;
	}
	// ステージデータ読み込み (layer15) 
	if (!readTiledJson(layer15StageData, "Assets/Config/StageData/ThirdStageMap.json", "layer15"))
	{
		printf("do'nt have Layer/layer15\n");
		return true;
	}
	// ステージデータ読み込み (layer16) 
	if (!readTiledJson(layer16StageData, "Assets/Config/StageData/ThirdStageMap.json", "layer16"))
	{
		printf("do'nt have Layer/layer16\n");
		return true;
	}
	// ステージデータ読み込み (layer17) 
	if (!readTiledJson(layer17StageData, "Assets/Config/StageData/ThirdStageMap.json", "layer17"))
	{
		printf("do'nt have Layer/layer17\n");
		return true;
	}

	// ステージデータ読み込み (layer18) 
	if (!readTiledJson(layer18StageData, "Assets/Config/StageData/ThirdStageMap.json", "layer18"))
	{
		printf("do'nt have Layer/layer18\n");
		return true;
	}

	// ステージデータ読み込み (player) 
	if (!readTiledJson(playerData, "Assets/Config/StageData/ThirdStageMap.json", "Player"))
	{
		printf("do'nt have Layer/Player\n");
		return true;
	}

	// ステージデータ読み込み (CameraDirecting)
	if (!readTiledJson(cameraDirectingData, "Assets/Config/StageData/ThirdStageMap.json", "CameraDirecting"))
	{
		printf("do'nt have Layer/CameraDirecting\n");
		return true;
	}

	return false;
}

/*
@fn ステージを生成する
*/
void ThirdStageCreator::CreateStage()
{
	// ステージデータを見てその情報ごとのclassを生成する
	for (int iy = 0; iy < sizeY; iy++)
	{
		for (int ix = 0; ix < sizeX; ix++)
		{
			// Layer1内を検索
			CreateLayer1(ix, iy);
			// Layer2内を検索
			CreateLayer2(ix, iy);
			// Layer3内を検索
			CreateLayer3(ix, iy);
			// Layer4内を検索
			CreateLayer4(ix, iy);
			// Layer5内を検索
			CreateLayer5(ix, iy);
			// Layer6内を検索
			CreateLayer6(ix, iy);
			// Layer7内を検索
			CreateLayer7(ix, iy);
			// Layer8内を検索
			CreateLayer8(ix, iy);
			// Layer9内を検索
			CreateLayer9(ix, iy);
			// Layer10内を検索
			CreateLayer10(ix, iy);
			// Layer11内を検索
			CreateLayer11(ix, iy);
			// Layer12内を検索
			CreateLayer12(ix, iy);
			// Layer13内を検索
			CreateLayer13(ix, iy);
			// Layer14内を検索
			CreateLayer14(ix, iy);
			// Layer15内を検索
			CreateLayer15(ix, iy);
			// Layer16内を検索
			CreateLayer16(ix, iy);
			// Layer17内を検索
			CreateLayer17(ix, iy);
			// Layer18内を検索
			CreateLayer18(ix, iy);
		}
	}
}

/*
@fn プレイヤーを生成する
*/
PlayerObject* ThirdStageCreator::CreatePlayer()
{

	// プレイヤーの位置情報検索
	for (int iy = 0; iy < sizeY; iy++)
	{
		for (int ix = 0; ix < sizeX; ix++)
		{
			// プレイヤーを生成する処理
			ProductionPlayer(playerData[iy][ix], ix, iy);
		}
	}

	// プレイヤーオブジェクトのポインタを返す
	return playerObject;

}

/*
@fn レイヤー1クリエイター
@brief  レイヤー1のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer1(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer1 = layer1StageData[_indexY][_indexX];
	// レイヤー1のマップオブジェクトのポジション
	Vector3 layer1Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[0]);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer1)
	{
	case(LAYER1_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer1Pos, BlockSize, Tag::GROUND);
		break;
	}
}

/*
@fn レイヤー2クリエイター
@brief  レイヤー2のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer2(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer2 = layer2StageData[_indexY][_indexX];
	// レイヤー2のマップオブジェクトのポジション
	Vector3 layer2Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[1]);
	// レイヤー2のスイッチ系マップオブジェクトのポジション
	Vector3 layer2SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[1] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer2)
	{
	case(LAYER2_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer2Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// パワーセルライトの生成
		new LightObject(layer2Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// パワーセルライトの生成
		new LightObject(layer2Pos, LightObjectSize, Tag::GROUND, false);
		break;
	}
}

/*
@fn レイヤー3クリエイター
@brief  レイヤー3のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer3(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer3 = layer3StageData[_indexY][_indexX];
	// レイヤー3のマップオブジェクトのポジション
	Vector3 layer3Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[2]);
	// レイヤー3のスイッチ系マップオブジェクトのポジション
	Vector3 layer3SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[2] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer3)
	{
	case(LAYER3_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer3Pos, BlockSize, Tag::GROUND);
		break;

	case(RIGHT_MOVE_ENEMY_PARTS):
		// 移動情報をセット
		SetMoveEnemyData(300.0f, Vector3::UnitY, 400.0f, MoveEnemyTag::RIGHT_MOVE);
		// 敵オブジェクト生成
		new MoveEnemyObject(layer3Pos, Tag::ENEMY, moveEnemyData);
		break;

	case(LEFT_MOVE_ENEMY_PARTS):
		// 移動情報をセット
		SetMoveEnemyData(300.0f, Vector3::NegUnitY, 400.0f, MoveEnemyTag::LEFT_MOVE);
		// 敵オブジェクト生成
		new MoveEnemyObject(layer3Pos, Tag::ENEMY, moveEnemyData);
		break;
	}
}

/*
@fn レイヤー4クリエイター
@brief  レイヤー4のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer4(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer4 = layer4StageData[_indexY][_indexX];
	// レイヤー4のマップオブジェクトのポジション
	Vector3 layer4Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[3]);
	// レイヤー4のスイッチ系マップオブジェクトのポジション
	Vector3 layer4SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[3] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer4)
	{
	case(LAYER4_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer4Pos, BlockSize, Tag::GROUND);
		break;
	}
}

/*
@fn レイヤー5クリエイター
@brief  レイヤー5のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer5(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer5 = layer5StageData[_indexY][_indexX];
	// レイヤー5のマップオブジェクトのポジション
	Vector3 layer5Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[4]);
	// レイヤー5のスイッチ系マップオブジェクトのポジション
	Vector3 layer5SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[4] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer5)
	{
	case(LAYER5_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer5Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// パワーセルライトの生成
		new LightObject(layer5Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// パワーセルライトの生成
		new LightObject(layer5Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(FIRST_SWITCH_PARTS):
		// 第一区画スイッチオブジェクト生成
		new SwitchBaseObject(layer5SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::FIRST_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer5SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(FIRST_MOVE_WALL_PARTS):
		// 第一区画の動く壁オブジェクト生成
		new MoveWallBlock(Vector3(layer5Pos.x, layer5Pos.y + ShiftMoveWallY, layer5Pos.z - ShiftMoveWallZ), BigMoveWallSize, Tag::FIRST_MOVE_WALL, MoveWallSpeed,
			Vector3(layer5Pos.x, layer5Pos.y, layer5Pos.z - BigMoveWallSize.z));
		break;

	case(RESPOWN_POINT_PARTS):
		// リスポーンポイントオブジェクト生成
		new RespawnPoint(layer5Pos, RespawnBox, Tag::RESPOWN_POINT);
		break;

	case(RIGHT_PUSH_BOX_NUMBER_1):
		// プッシュボード固有のデータ構造体をセット
		SetPushBoxData(Vector3(0.0f, 1200.0f, 0.0f), Vector3::UnitY, 1500.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		// ケースごとに方向の違う押し出しボックスの生成
		new PushBoxObject(layer5Pos, BlockSize, Tag::PUSH_BOX, pushBoxData);
		break;

	case(RIGHT_PUSH_BOX_NUMBER_2):
		// プッシュボード固有のデータ構造体をセット
		SetPushBoxData(Vector3(0.0f, 1200.0f, 0.0f), Vector3::UnitY, 1450.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		// ケースごとに方向の違う押し出しボックスの生成
		new PushBoxObject(layer5Pos, BlockSize, Tag::PUSH_BOX, pushBoxData);
		break;

	case(RIGHT_PUSH_BOX_NUMBER_3):
		// プッシュボード固有のデータ構造体をセット
		SetPushBoxData(Vector3(0.0f, 1200.0f, 0.0f), Vector3::UnitY, 1400.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		// ケースごとに方向の違う押し出しボックスの生成
		new PushBoxObject(layer5Pos, BlockSize, Tag::PUSH_BOX, pushBoxData);
		break;

	case(LEFT_PUSH_BOX_NUMBER_1):
		// プッシュボード固有のデータ構造体をセット
		SetPushBoxData(Vector3(0.0f, -1200.0f, 0.0f), Vector3::NegUnitY, 1500.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		// ケースごとに方向の違う押し出しボックスの生成
		new PushBoxObject(layer5Pos, BlockSize, Tag::PUSH_BOX, pushBoxData);
		break;

	case(LEFT_PUSH_BOX_NUMBER_2):
		// プッシュボード固有のデータ構造体をセット
		SetPushBoxData(Vector3(0.0f, -1200.0f, 0.0f), Vector3::NegUnitY, 1450.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		// ケースごとに方向の違う押し出しボックスの生成
		new PushBoxObject(layer5Pos, BlockSize, Tag::PUSH_BOX, pushBoxData);
		break;

	case(TRACKING_ENEMY_PARTS):
		// 追跡する敵の生成
		new TrackingEnemyObject(layer5Pos, Tag::ENEMY, 600.0f, 1400.0f);
		break;
	}
}

/*
@fn レイヤー6クリエイター
@brief  レイヤー6のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer6(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer6 = layer6StageData[_indexY][_indexX];
	// レイヤー6のマップオブジェクトのポジション
	Vector3 layer6Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[5]);
	// レイヤー6のスイッチ系マップオブジェクトのポジション
	Vector3 layer6SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[5] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer6)
	{
	case(LAYER6_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer6Pos, BlockSize, Tag::GROUND);
		break;

	case(UP_MOVE_BLOCK_PARTS):
		// 上下移動のblockを生成
		SetMoveBlockData(600.0f, Vector3::UnitZ, 500.0f, Vector3(50.0f, 1000.0f, 600.0f), MoveDirectionTag::MOVE_Z);
		new MoveBlockObject(layer6Pos, Tag::MOVE_GROUND, moveBlockData);
		break;
	}
}

/*
@fn レイヤー7クリエイター
@brief  レイヤー7のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer7(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer7 = layer7StageData[_indexY][_indexX];
	// レイヤー7のマップオブジェクトのポジション
	Vector3 layer7Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[6]);
	// レイヤー7のスイッチ系マップオブジェクトのポジション
	Vector3 layer7SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[6] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer7)
	{
	case(LAYER7_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer7Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// パワーセルライトの生成
		new LightObject(layer7Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// パワーセルライトの生成
		new LightObject(layer7Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer7SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(SECOND_SWITCH_PARTS):
		// 第二区画スイッチオブジェクト生成
		new SwitchBaseObject(layer7SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(SECOND_MOVE_WALL_PARTS):
		// 第二区画の動く壁オブジェクト生成
		lastMoveWallBlock = new MoveWallBlock(Vector3(layer7Pos.x, layer7Pos.y + ShiftMoveWallY, layer7Pos.z - ShiftMoveWallZ), BigMoveWallSize, Tag::CLEAR_SCENE_MOVE_WALL, MoveWallSpeed,
			Vector3(layer7Pos.x, layer7Pos.y, layer7Pos.z - BigMoveWallSize.z));
		break;

	case(BREAK_BLOCK_PARTS):
		// 壊れるblockを生成
		new BreakBlockObject(layer7Pos, BlockSize, Tag::BREAK_GROUND);
		break;

	case(COLLECTION_SECOND):
		// 2番目の収集物を生成
		secondCollectionObject = new CollectionObject(layer7Pos, Tag::COLLECTION, CollectionTag::SECOND);
		break;
	}
}

/*
@fn レイヤー8クリエイター
@brief  レイヤー8のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer8(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer8 = layer8StageData[_indexY][_indexX];
	// レイヤー8のマップオブジェクトのポジション
	Vector3 layer8Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[7]);
	// レイヤー8のスイッチ系マップオブジェクトのポジション
	Vector3 layer8SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[7] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer8)
	{
	case(LAYER8_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer8Pos, BlockSize, Tag::GROUND);
		break;
	case(BREAK_BLOCK_PARTS):
		// 壊れるblockを生成
		new BreakBlockObject(layer8Pos, BlockSize, Tag::BREAK_GROUND);
		break;

	case(COLLECTION_THIRD):
		// 3番目の収集物を生成
		thirdCollectionObject = new CollectionObject(layer8Pos, Tag::COLLECTION, CollectionTag::THIRD);
		break;

	}
}

/*
@fn レイヤー9クリエイター
@brief  レイヤー9のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer9(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer9 = layer9StageData[_indexY][_indexX];
	// レイヤー9のマップオブジェクトのポジション
	Vector3 layer9Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[8]);
	// レイヤー9のスイッチ系マップオブジェクトのポジション
	Vector3 layer9SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[8] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer9)
	{
	case(LAYER9_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer9Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// パワーセルライトの生成
		new LightObject(layer9Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// パワーセルライトの生成
		new LightObject(layer9Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(SECOND_SWITCH_PARTS):
		// 第二区画スイッチオブジェクト生成
		new SwitchBaseObject(layer9SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer9SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NEEDLE_PARTS):
		// 二ードルオブジェクト生成
		new NeedlePanelObject(layer9SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(RESPOWN_POINT_PARTS):
		// リスポーンポイントオブジェクト生成
		new RespawnPoint(layer9Pos, RespawnBox, Tag::RESPOWN_POINT);
		break;

	case(BREAK_BLOCK_PARTS):
		// 壊れるblockを生成
		new BreakBlockObject(layer9Pos, BlockSize, Tag::BREAK_GROUND);
		break;

	case(BOMB_PARTS):
		// 爆発物を生成
		new ExplosionObject(layer9Pos, Tag::BOMB);
		break;
	}
}

/*
@fn レイヤー10クリエイター
@brief  レイヤー10のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer10(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer10 = layer10StageData[_indexY][_indexX];
	// レイヤー10のマップオブジェクトのポジション
	Vector3 layer10Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[9]);
	// レイヤー10のスイッチ系マップオブジェクトのポジション
	Vector3 layer10SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[9] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer10)
	{
	case(LAYER10_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer10Pos, BlockSize, Tag::GROUND);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer10SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NORMAL_ENEMY_PARTS):
		// 動かない敵の生成
		new NormalEnemyObject(layer10Pos, Tag::ENEMY);
		break;

	case(RIGHT_MOVE_ENEMY_PARTS):
		// 移動情報をセット
		SetMoveEnemyData(500.0f, Vector3::UnitY, 600.0f, MoveEnemyTag::RIGHT_MOVE);
		// 敵オブジェクト生成
		new MoveEnemyObject(layer10Pos, Tag::ENEMY, moveEnemyData);
		break;

	case(BREAK_BLOCK_PARTS):
		// 壊れるblockを生成
		new BreakBlockObject(layer10Pos, BlockSize, Tag::BREAK_GROUND);
		break;
	case(BOMB_PARTS):
		// 爆発物を生成
		new ExplosionObject(layer10Pos, Tag::BOMB);
		break;
	}
}

/*
@fn レイヤー11クリエイター
@brief  レイヤー11のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer11(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer11 = layer11StageData[_indexY][_indexX];
	// レイヤー11のマップオブジェクトのポジション
	Vector3 layer11Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[10]);
	// レイヤー11のスイッチ系マップオブジェクトのポジション
	Vector3 layer11SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[10] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer11)
	{
	case(LAYER11_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer11Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// パワーセルライトの生成
		new LightObject(layer11Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// パワーセルライトの生成
		new LightObject(layer11Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(LEFT_MOVE_ENEMY_PARTS):
		// 移動情報をセット
		SetMoveEnemyData(500.0f, Vector3::NegUnitY, 600.0f, MoveEnemyTag::LEFT_MOVE);
		// 敵オブジェクト生成
		new MoveEnemyObject(layer11Pos, Tag::ENEMY, moveEnemyData);
		break;

	case(BREAK_BLOCK_PARTS):
		// 壊れるblockを生成
		new BreakBlockObject(layer11Pos, BlockSize, Tag::BREAK_GROUND);
		break;
	}
}

/*
@fn レイヤー12クリエイター
@brief  レイヤー12のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer12(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer12 = layer12StageData[_indexY][_indexX];
	// レイヤー12のマップオブジェクトのポジション
	Vector3 layer12Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[11]);
	// レイヤー12のスイッチ系マップオブジェクトのポジション
	Vector3 layer12SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[11] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer12)
	{
	case(LAYER12_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer12Pos, BlockSize, Tag::GROUND);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer12SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(NORMAL_ENEMY_PARTS):
		// 動かない敵の生成
		new NormalEnemyObject(layer12Pos, Tag::ENEMY);
		break;

	case(RIGHT_MOVE_ENEMY_PARTS):
		// 移動情報をセット
		SetMoveEnemyData(500.0f, Vector3::UnitY, 600.0f, MoveEnemyTag::RIGHT_MOVE);
		// 敵オブジェクト生成
		new MoveEnemyObject(layer12Pos, Tag::ENEMY, moveEnemyData);
		break;

	case(BREAK_BLOCK_PARTS):
		// 壊れるblockを生成
		new BreakBlockObject(layer12Pos, BlockSize, Tag::BREAK_GROUND);
		break;
	}
}

/*
@fn レイヤー13クリエイター
@brief  レイヤー13のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer13(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer13 = layer13StageData[_indexY][_indexX];
	// レイヤー13のマップオブジェクトのポジション
	Vector3 layer13Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[12]);
	// レイヤー13のスイッチ系マップオブジェクトのポジション
	Vector3 layer13SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[12] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer13)
	{
	case(LAYER13_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer13Pos, BlockSize, Tag::GROUND);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer13SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(TRACKING_ENEMY_PARTS):
		// 追跡する敵の生成
		new TrackingEnemyObject(layer13Pos, Tag::ENEMY, 600.0f, 1400.0f);
		break;

	case(LEFT_MOVE_ENEMY_PARTS):
		// 移動情報をセット
		SetMoveEnemyData(500.0f, Vector3::NegUnitY, 600.0f, MoveEnemyTag::LEFT_MOVE);
		// 敵オブジェクト生成
		new MoveEnemyObject(layer13Pos, Tag::ENEMY, moveEnemyData);
		break;

	case(BREAK_BLOCK_PARTS):
		// 壊れるblockを生成
		new BreakBlockObject(layer13Pos, BlockSize, Tag::BREAK_GROUND);
		break;

	case(BOMB_PARTS):
		// 爆発物を生成
		new ExplosionObject(layer13Pos, Tag::BOMB);
		break;
	}
}

/*
@fn レイヤー14クリエイター
@brief  レイヤー14のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer14(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer14 = layer14StageData[_indexY][_indexX];
	// レイヤー14のマップオブジェクトのポジション
	Vector3 layer14Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[13]);
	// レイヤー14のスイッチ系マップオブジェクトのポジション
	Vector3 layer14SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[13] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer14)
	{
	case(LAYER14_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer14Pos, BlockSize, Tag::GROUND);
		break;

	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// パワーセルライトの生成
		new LightObject(layer14Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// パワーセルライトの生成
		new LightObject(layer14Pos, LightObjectSize, Tag::GROUND, false);
		break;

	case(NEEDLE_PARTS):
		// 二ードルオブジェクト生成
		new NeedlePanelObject(layer14SwitchPos, NeedlePanelSize, Tag::NEEDLE_PANEL);
		break;

	case(JUMP_SWITCH_PARTS):
		// ジャンプスイッチオブジェクト生成
		new JumpSwitchObject(layer14SwitchPos, JumpSwitchSize, Tag::JUMP_SWITCH);
		break;

	case(TRACKING_ENEMY_PARTS):
		// 追跡する敵の生成
		new TrackingEnemyObject(layer14Pos, Tag::ENEMY, 600.0f, 1400.0f);
		break;

	case(LEFT_PUSH_BOX_NUMBER_3):
		// プッシュボード固有のデータ構造体をセット
		SetPushBoxData(Vector3(0.0f, -1200.0f, 0.0f), Vector3::NegUnitY, 1500.0f, 0.3f, MoveDirectionTag::MOVE_Y);
		// ケースごとに方向の違う押し出しボックスの生成
		new PushBoxObject(layer14Pos, BlockSize, Tag::PUSH_BOX, pushBoxData);
		break;

	case(RESPOWN_POINT_PARTS):
		// リスポーンポイントオブジェクト生成
		new RespawnPoint(layer14Pos, RespawnBox, Tag::RESPOWN_POINT);
		break;

	case(COLLECTION_FIRST):
		// 1番目の収集物を生成
		firstCollectionObject = new CollectionObject(layer14Pos, Tag::COLLECTION, CollectionTag::FIRST);
		break;

	case(NORMAL_ENEMY_PARTS):
		// 動かない敵の生成
		new NormalEnemyObject(layer14Pos, Tag::ENEMY);
		break;

	case(RIGHT_MOVE_ENEMY_PARTS):
		// 移動情報をセット
		SetMoveEnemyData(500.0f, Vector3::UnitY, 600.0f, MoveEnemyTag::RIGHT_MOVE);
		// 敵オブジェクト生成
		new MoveEnemyObject(layer14Pos, Tag::ENEMY, moveEnemyData);
		break;

	case(BREAK_BLOCK_PARTS):
		// 壊れるblockを生成
		new BreakBlockObject(layer14Pos, BlockSize, Tag::BREAK_GROUND);
		break;
	}
}

/*
@fn レイヤー15クリエイター
@brief  レイヤー15のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer15(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer15 = layer15StageData[_indexY][_indexX];
	// レイヤー8のマップオブジェクトのポジション
	Vector3 layer15Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[14]);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer15)
	{
	case(LAYER15_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer15Pos, BlockSize, Tag::GROUND);
		break;

	case(NORMAL_ENEMY_PARTS):
		// 動かない敵の生成
		new NormalEnemyObject(layer15Pos, Tag::ENEMY);
		break;

	case(LEFT_MOVE_ENEMY_PARTS):
		// 移動情報をセット
		SetMoveEnemyData(500.0f, Vector3::NegUnitY, 600.0f, MoveEnemyTag::LEFT_MOVE);
		// 敵オブジェクト生成
		new MoveEnemyObject(layer15Pos, Tag::ENEMY, moveEnemyData);
		break;

	case(RIGHT_MOVE_BLOCK_PARTS):
		// 右に動くblockを生成
		SetMoveBlockData(1100.0f, Vector3::UnitY, 900.0f, Vector3(50.0f, 900.0f, 1000.0f), MoveDirectionTag::MOVE_Y);
		new MoveBlockObject(layer15Pos, Tag::MOVE_GROUND, moveBlockData);
		break;

	case(LEFT_MOVE_BLOCK_PARTS):
		// 左に動くblockを生成
		SetMoveBlockData(1100.0f, Vector3::NegUnitY, 900.0f, Vector3(50.0f, 900.0f, 1000.0f), MoveDirectionTag::MOVE_Y);
		new MoveBlockObject(layer15Pos, Tag::MOVE_GROUND, moveBlockData);
		break;

	case(BREAK_BLOCK_PARTS):
		// 壊れるblockを生成
		new BreakBlockObject(layer15Pos, BlockSize, Tag::BREAK_GROUND);
		break;
	}
}

/*
@fn レイヤー16クリエイター
@brief  レイヤー16のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer16(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer16 = layer16StageData[_indexY][_indexX];
	// レイヤー16のマップオブジェクトのポジション
	Vector3 layer16Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[15]);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer16)
	{
	case(LAYER16_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer16Pos, BlockSize, Tag::GROUND);
		break;

	case(NORMAL_ENEMY_PARTS):
		// 動かない敵の生成
		new NormalEnemyObject(layer16Pos, Tag::ENEMY);
		break;

	case(RIGHT_MOVE_ENEMY_PARTS):
		// 移動情報をセット
		SetMoveEnemyData(500.0f, Vector3::UnitY, 600.0f, MoveEnemyTag::RIGHT_MOVE);
		// 敵オブジェクト生成
		new MoveEnemyObject(layer16Pos, Tag::ENEMY, moveEnemyData);
		break;
	}
}

/*
@fn レイヤー17クリエイター
@brief  レイヤー17のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer17(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer17 = layer17StageData[_indexY][_indexX];
	// レイヤー17のマップオブジェクトのポジション
	Vector3 layer17Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[16]);
	// レイヤー17のスイッチ系マップオブジェクトのポジション
	Vector3 layer17SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[16] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer17)
	{
	case(LAYER17_BLOCK_PARTS):
		// ブロックオブジェクト生成
		new GroundObject(layer17Pos, BlockSize, Tag::GROUND);
		break;

	case(LEFT_MOVE_ENEMY_PARTS):
		// 移動情報をセット
		SetMoveEnemyData(500.0f, Vector3::NegUnitY, 600.0f, MoveEnemyTag::LEFT_MOVE);
		// 敵オブジェクト生成
		new MoveEnemyObject(layer17Pos, Tag::ENEMY, moveEnemyData);
		break;
	}
}

/*
@fn レイヤー18クリエイター
@brief  レイヤー18のマップデータに含まれるオブジェクトの生成を行う
@param	_indexX 検索するマップデータの添え字X
@param	_indexY 検索するマップデータの添え字Y
*/
void ThirdStageCreator::CreateLayer18(int _indexX, int _indexY)
{
	// ステージデータ配列からマップデータをもらう
	const unsigned int Layer18 = layer18StageData[_indexY][_indexX];
	// レイヤー16のマップオブジェクトのポジション
	Vector3 layer18Pos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[17]);
	// レイヤー17のスイッチ系マップオブジェクトのポジション
	Vector3 layer18SwitchPos = Vector3(Offset * _indexX, -Offset * _indexY, objectPositionZ[17] - ShiftSwitchPositionZ);

	// マップデータを見てそれぞれのオブジェクトを生成
	switch (Layer18)
	{
	case(POWERCELLS_LIGHT_PARTS_RIGHT):
		// パワーセルライトの生成
		new LightObject(layer18Pos, LightObjectSize, Tag::GROUND, true);
		break;

	case(POWERCELLS_LIGHT_PARTS_LEFT):
		// パワーセルライトの生成
		new LightObject(layer18Pos, LightObjectSize, Tag::GROUND, false);
		break;
	case(CLEAR_OBJECT_PARTS):
		// ステージクリアオブジェクト生成
		new NextSceneObject(layer18Pos, Tag::CLEAR_POINT, playerObject, lastMoveWallBlock);
		break;

	case(SECOND_SWITCH_PARTS):
		// 第二区画スイッチオブジェクト生成
		new SwitchBaseObject(layer18SwitchPos, SwitchBaseSize, Tag::GROUND, Tag::CLEAR_SCENE_SWITCH);
		break;

	case(RESPOWN_POINT_PARTS):
		// リスポーンポイントオブジェクト生成
		new RespawnPoint(layer18Pos, RespawnBox, Tag::RESPOWN_POINT);
		break;

	case(DOWN_MOVE_BLOCK_PARTS):
		// 下に動くblockを生成
		SetMoveBlockData(600.0f, Vector3::NegUnitZ, 500.0f, Vector3(50.0f, 1000.0f, 600.0f), MoveDirectionTag::MOVE_Z);
		new MoveBlockObject(layer18Pos, Tag::MOVE_GROUND, moveBlockData);
		break;
	}
}