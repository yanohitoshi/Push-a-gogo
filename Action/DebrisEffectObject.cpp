//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "DebrisEffectObject.h"
#include "MeshComponent.h"
#include "Mesh.h"

/*
@fn コンストラクタ
@param	親となるクラスのポインタ
@param	方向ベクトル
*/
DebrisEffectObject::DebrisEffectObject(const Vector3& _pos, const Vector3& _direction)
	: GameObject(false,Tag::GROUND)
	, MovePower(50.0f)
	, MaxLifeCount(60)
	, SpeedRandValue(1500)
	, SpeedLowestValue(1000)
	, RotateRandValue(361)
	, RotateLowestValue(50)
	, FallSpeed(0.05f)
{
	//GameObjectメンバ変数の初期化
	SetPosition(_pos);
	SetScale(Vector3(2.0f,2.0f,2.0f));
	tag = Tag::GROUND;
	state = Active;
	isPushBackToPlayer = false;
	isCheckGroundToPlayer = false;
	isPushBackToCamera = false;

	direction = _direction;
	// 生存時間初期化
	lifeCount = MaxLifeCount;

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(GRAPHICS_RESOURCE->CreateMesh("Assets/Model/Environment/Ground/model/debrisGround.gpmesh"));
	//メッシュ情報取得
	mesh = meshComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();

	// ランダムな速度を得る
	moveSpeed = (float)(rand() % SpeedRandValue + SpeedLowestValue);

	// ランダムな値で回転を掛ける
	Rotation(this, (float)(rand() % RotateRandValue + RotateLowestValue), Vector3::UnitX);
	Rotation(this, (float)(rand() % RotateRandValue + RotateLowestValue), Vector3::UnitY);
	Rotation(this, (float)(rand() % RotateRandValue + RotateLowestValue), Vector3::UnitZ);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
DebrisEffectObject::~DebrisEffectObject()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void DebrisEffectObject::UpdateGameObject(float _deltaTime)
{
	// 生存時間を減らす
	LifeCountDown();
	velocity = direction * moveSpeed;
	SetPosition(position + velocity * _deltaTime);

	// z軸方向ベクトルをマイナス方向にしていく
	direction.z -= FallSpeed;

	// -1.0以下になったら1.0で固定
	if (direction.z <= -1.0f)
	{
		direction.z = -1.0f;
	}

	// ライフカウントが0以下になったら
	if (lifeCount <= 0)
	{
		// ステータスをdeadに変更
		state = State::Dead;
		SetState(state);
	}
}

/*
@fn 生存時間のカウントダウン
*/
void DebrisEffectObject::LifeCountDown()
{
	//生存時間がゼロになるとこのオブジェクトを更新終了する
	if (lifeCount <= 0)
	{
		meshComponent->SetVisible(false);
		SetState(State::Dead);

	}
	else
	{
		meshComponent->SetVisible(true);
		lifeCount--;
	}
}