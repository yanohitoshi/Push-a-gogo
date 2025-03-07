//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "FallExplosionObject.h"
#include "FallExplosionArea.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "BoxCollider.h"
#include "ExplosionObjectStateBase.h"
#include "FallExplosionObjectStateIdle.h"
#include "ExplosionObjectStateFall.h"
#include "ExplosionObjectStateExplosion.h"
#include "FallExplosionObjectStateRespawn.h"
#include "ExplosionObjectEffectManager.h"
#include "ExplosionArea.h"

/*
@fn コンストラクタ
@param	親クラスのポインタ
@param	ポジション
@param	オブジェクト判別用tag
*/
FallExplosionObject::FallExplosionObject(FallExplosionArea* _owner, const Vector3& _pos, const Tag _objectTag)
	: ExplosionObjectBase(_objectTag)
{
	//GameObjectメンバ変数の初期化
	velocity.Zero;

	position = _pos;
	SetPosition(position);
	// 初期ポジションを保存
	firstPosition = position;
	fallArea = _owner->GetArea();
	owner = _owner;
	SetScale(Vector3(0.5f, 0.5f, 0.5f));
	isStartExplosion = false;
	isHitJumpAttackPlayer = false;
	isHitExplosionObject = false;
	hitPosition = Vector3(0.0f, 0.0f, 0.0f);

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(GRAPHICS_RESOURCE->CreateMesh("Assets/Model/Environment/Bomb/model/bomb.gpmesh"));
	meshComponent->SetEmissiveColor(Color::LightBlue);

	//メッシュ情報取得
	mesh = meshComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();

	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::FALL_BOMB_TAG, GetOnCollisionFunc());
	AABB aabb = { Vector3(-100.0f,-100.0f,-100.0f),Vector3(100.0f,100.0f,100.0f) };
	boxCollider->SetObjectBox(aabb);

	// mapにステートパターンクラスを追加
	AddStatePoolMap(new FallExplosionObjectStateIdle(), ExplosionObjectState::IDLE);
	AddStatePoolMap(new ExplosionObjectStateFall(), ExplosionObjectState::FALL);
	AddStatePoolMap(new ExplosionObjectStateExplosion(this), ExplosionObjectState::EXPLOSION);
	AddStatePoolMap(new FallExplosionObjectStateRespawn(), ExplosionObjectState::RESPAWN);

	nowState = ExplosionObjectState::NUM;
	nextState = ExplosionObjectState::RESPAWN;

	new ExplosionObjectEffectManager(this);
	new ExplosionArea(Tag::EXPLOSION_AREA, this);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
FallExplosionObject::~FallExplosionObject()
{
	// Mapの後片付け
	RemoveStatePoolMap(ExplosionObjectState::IDLE);
	RemoveStatePoolMap(ExplosionObjectState::FALL);
	RemoveStatePoolMap(ExplosionObjectState::EXPLOSION);
	RemoveStatePoolMap(ExplosionObjectState::RESPAWN);
	ClearStatePoolMap();
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void FallExplosionObject::UpdateGameObject(float _deltaTime)
{
	// オーナーの落下開始フラグがtrueだったら
	if (owner->GetIsFallStart())
	{
		// trueにする
		isFallStart = true;
	}
	else
	{
		isFallStart = false;
	}

	// ステート外部からステート変更があったか？
	if (nowState != nextState)
	{
		//マップの中に追加するアクターのコンテナがあるかどうかを調べる
		auto state = statePoolMap.find(nextState);
		if (state != statePoolMap.end())
		{
			statePoolMap[nextState]->Enter(this, _deltaTime);
		}

		nowState = nextState;
		return;
	}

	// ステート実行
	//マップの中に追加するアクターのコンテナがあるかどうかを調べる
	auto state = statePoolMap.find(nowState);
	if (state != statePoolMap.end())
	{
		nextState = statePoolMap[nowState]->Update(this, _deltaTime);
	}

	// ステート内部からステート変更あったか？
	if (nowState != nextState)
	{
		auto state = statePoolMap.find(nextState);
		if (state != statePoolMap.end())
		{
			statePoolMap[nextState]->Enter(this, _deltaTime);
		}
		nowState = nextState;
	}
}

/*
@fn 当たり判定が行われHitした際に呼ばれる関数
@param	当たったGameObject
@param	当たり判定タグ
*/
void FallExplosionObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// 触れたら爆発するオブジェクトか判定
	bool isHitExplosion = _physicsTag == PhysicsTag::GROUND_TAG || _physicsTag == PhysicsTag::MOVE_GROUND_TAG ||
		_physicsTag == PhysicsTag::BREAK_GROUND_TAG || _physicsTag == PhysicsTag::ENEMY_TAG;

	if (isHitExplosion)
	{
		isHitExplosionObject = true;
	}
}
