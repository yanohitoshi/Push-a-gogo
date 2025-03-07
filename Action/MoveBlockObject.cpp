//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "MoveBlockObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "BoxCollider.h"

/*
@fn コンストラクタ
@param	ポジション
@param	objectのサイズ
@param	オブジェクト判別用tag
@param  動く床に必要なデータ構造体
*/
MoveBlockObject::MoveBlockObject(const Vector3& _p, const Tag& _objectTag, MoveBlockData _data)
	: GameObject(false, _objectTag)
	, CorrectionAabbValue(0.1f)
{
	//GameObjectメンバ変数の初期化
	SetPosition(_p);
	SetScale(_data.objectSize);
	tag = _objectTag;
	state = Active;
	direction = _data.direction;
	initPos = _p;
	goalPos = initPos + direction * _data.distance;
	moveSpeed = _data.speed;
	moveTag = _data.tag;
	inversionFlag = false;
	isPushBackToPlayer = true;
	isSendVelocityToPlayer = true;
	isCheckGroundToPlayer = true;

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(GRAPHICS_RESOURCE->CreateMesh("Assets/Model/Environment/Ground/model/lightGround.gpmesh"));

	//メッシュ情報取得
	mesh = meshComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();

	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::MOVE_GROUND_TAG, GetOnCollisionFunc());
	aabb = mesh->GetBox();
	//プレイヤーがすり抜けないようにAABBのサイズを補正
	aabb.max.y += CorrectionAabbValue;
	aabb.min.y -= CorrectionAabbValue;
	boxCollider->SetObjectBox(aabb);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
MoveBlockObject::~MoveBlockObject()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void MoveBlockObject::UpdateGameObject(float _deltaTime)
{
	//worldboxを渡す
	aabb = boxCollider->GetWorldBox();

	// 可動処理
	MovableProcess();

	// 移動状態確認
	CheckInversionProcess();

	// ポジションに速度を足す
	position = position + velocity * _deltaTime;

	// ポジションを更新
	SetPosition(position);

}

/*
@fn 可動処理関数
*/
void MoveBlockObject::MovableProcess()
{
	// 反転するかどうかフラグを判定しそれに応じて速度を付与
	if (inversionFlag == false)
	{
		// 通常の速度を代入
		velocity = direction * moveSpeed;
	}
	else if (inversionFlag == true)
	{
		// 反転した速度を代入
		velocity = direction * moveSpeed * -1.0f;
	}
}

/*
@fn 反転チェック処理関数
*/
void MoveBlockObject::CheckInversionProcess()
{
	// 動く方向のタグを見て処理を変える
	switch (moveTag)
	{
	case MOVE_X:
		// X軸の処理
		CheckAxisX();
		break;
	case MOVE_Y:
		// Y軸の処理
		CheckAxisY();
		break;
	case MOVE_Z:
		// Z軸の処理
		CheckAxisZ();
		break;
	}
}

/*
@fn X軸反転チェック処理関数
*/
void MoveBlockObject::CheckAxisX()
{
	// 到達点に達していたら反転
	if (position.x >= goalPos.x && direction.x == 1.0f || position.x <= goalPos.x && direction.x == -1.0f)
	{
		inversionFlag = true;
	}

	// 元の位置に達していたら反転
	if (position.x <= initPos.x && direction.x == 1.0f || position.x >= initPos.x && direction.x == -1.0f)
	{
		inversionFlag = false;
	}
}

/*
@fn Y軸反転チェック処理関数
*/
void MoveBlockObject::CheckAxisY()
{
	// 到達点に達していたら反転
	if (position.y >= goalPos.y && direction.y == 1.0f || position.y <= goalPos.y && direction.y == -1.0f)
	{
		inversionFlag = true;
	}

	// 元の位置に達していたら反転
	if (position.y <= initPos.y && direction.y == 1.0f || position.y >= initPos.y && direction.y == -1.0f)
	{
		inversionFlag = false;
	}
}

/*
@fn Z軸反転チェック処理関数
*/
void MoveBlockObject::CheckAxisZ()
{
	// 到達点に達していたら反転
	if (position.z >= goalPos.z && direction.z == 1.0f || position.z <= goalPos.z && direction.z == -1.0f)
	{
		inversionFlag = true;
	}

	// 元の位置に達していたら反転
	if (position.z <= initPos.z && direction.z == 1.0f || position.z >= initPos.z && direction.z == -1.0f)
	{
		inversionFlag = false;
	}
}