#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include <vector>
#include <functional>
#include "Math.h"
#include "Collision.h"
#include <unordered_map>
#include "Game.h"

// クラスの前方宣言
class Vector3;
class Matrix4;
class Component;
struct InputState;
class ColliderComponent;
class MainCameraObject;

/*
@brief	ゲームオブジェクトの状態
*/
enum State
{
	//アクティブ
	Active,
	//更新が停止している
	Paused,
	//オブジェクトの更新が終了(外部からのみActiveに変更可能)
	Dead
};

/*
@enum　GameObjectタグ(objectがなんなのかの判別に使用)
*/
enum Tag
{
	OTHER,
	CAMERA,
	PLAYER,
	GROUND,
	MOVE_GROUND,
	WALL,
	NEEDLE,
	NEEDLE_PANEL,
	PUSH_BOARD,
	PUSH_BOX,
	FIRST_MOVE_WALL,
	SECOND_MOVE_WALL,
	NEXT_SCENE_MOVE_WALL,
	CLEAR_SCENE_MOVE_WALL,
	TUTORIAL_MOVE_WALL,
	TUTORIAL_SWITCH,
	FIRST_SWITCH,
	SECOND_SWITCH,
	NEXT_SCENE_SWITCH,
	CLEAR_SCENE_SWITCH,
	JUMP_SWITCH,
	SWITCH_BASE,
	GROUND_CHECK,
	SCENE,
	CLEAR_POINT,
	NEXT_SCENE_POINT,
	RESPOWN_POINT,
	TUTORIAL_CLEAR_POINT,
	UI,
	TITLE_OBJECT,
	TITLE_PLAYER,
	PARTICLE,
};

/*
@enum　動く方向のタグ
*/
enum MoveDirectionTag
{
	MOVE_X,
	MOVE_Y,
	MOVE_Z
};

class GameObject
{
public:
	/*
	@fn コンストラクタ
	@param	再利用するかどうかのフラグ
	@param	オブジェクト判別用tag
	*/
	GameObject(bool _reUseGameObject,const Tag _objectTag);
	virtual ~GameObject();

	/*
	@brief	フレーム毎の処理
	@param	最後のフレームを完了するのに要した時間
	*/
	void Update(float _deltaTime);

	/*
	@brief	アタッチされてるコンポーネントのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateComponents(float _deltaTime);

	/*
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void UpdateGameObject(float _deltaTime);

	/*
	@fn 入力状態を受け取りGameObjectとComponentの入力更新関数を呼び出す
	*/
	void ProcessInput(const InputState& _keyState);

	/*
	@fn 入力を引数で受け取る更新関数
	@brief 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
	*/
	virtual void GameObjectInput(const InputState& _keyState);

	/*
	@brief	コンポーネントを追加する
	@param	追加するコンポーネントのポインタ
	*/
	void AddComponent(Component* _component);

	/*
	@brief	コンポーネントを削除する
	@param	削除するコンポーネントのポインタ
	*/
	void RemoveComponent(Component* _component);

	/*
	@fn 現在の仕様上行うことができない処理を外部から強引に行うための関数
	@exsample ゲームオブジェクト全体の更新が停止中に対象のゲームオブジェクトを更新する
	*/
	void ExceptionUpdate();
	/*
	@brief	Transformのワールド変換
	*/
	void ComputeWorldTransform();

	/*
	@brief　オブジェクトのポジションを取得する
	@return	position
	*/
	const Vector3& GetPosition() const { return position; }

	/*
	@brief　オブジェクトのポジションを設定する
	@param	position
	*/
	virtual void SetPosition(const Vector3& _pos) { position = _pos; recomputeWorldTransform = true; }
	bool GetRecomputeWorldTransform() { return recomputeWorldTransform; }

	/*
	@brief　オブジェクトのスケールを取得する
	@return	scale
	*/
	Vector3 GetScaleFloat() const { return scale; }

	/*
	@brief　オブジェクトのスケールを設定する(x.y.zの比率が同じとき)
	@param	scale float型
	*/
	void SetScale(float _scale) { scale.x = _scale; scale.y = _scale; scale.z = _scale; recomputeWorldTransform = true; }
	
	/*
	@brief　オブジェクトのスケールを設定する(x.y.zの比率が違うとき)
	@param	scale Vector3型
	*/
	void SetScale(Vector3 _scale) { scale.x = _scale.x; scale.y = _scale.y; scale.z = _scale.z; recomputeWorldTransform = true; }
	
	/*
	@brief　オブジェクトのスケールを取得(x.y.zの比率が同じとき)
	@return	scale Vector3型
	*/
	float GetScale() { return scale.x; }
	
	/*
	@brief　オブジェクトのスケールを取得する(x.y.zの比率が違うとき)
	@return	scale Vector3型
	*/
	Vector3 GetScaleVec() {return scale;}
	/*
	@brief　オブジェクトのクォータニオンを取得する
	@return	rotation（Quaternion型）
	*/
	const Quaternion& GetRotation() const { return rotation; }

	/*
	@brief　オブジェクトのクォータニオンを設定する
	@param	rotation（Quaternion型）
	*/
	virtual void SetRotation(const Quaternion& _qotation) { rotation = _qotation;  recomputeWorldTransform = true; }

	/*
	@brief　オブジェクトの状態を取得する
	@return	state
	*/
	State GetState() const { return state; }

	/*
	@brief　オブジェクトの状態を設定する
	@param	state
	*/
	virtual void SetState(State _state) { state = _state; }

	/*
	@brief　オブジェクトのワールド行列を取得する
	@return	worldTransform
	*/
	const Matrix4& GetWorldTransform() const { return worldTransform; }

	/*
	@brief　オブジェクトの前方を表すベクトルを取得する
	@param	forward(Vector3型)
	*/
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitZ, rotation); }

	/*
	@brief　オブジェクトの右を表すベクトルを取得する
	@param	right(Vector3型)
	*/
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitX, rotation); }

	/*
	@brief　オブジェクトの上を表すベクトルを取得する
	@param	up(Vector3型)
	*/
	Vector3 GetUp() const { return Vector3::Transform(Vector3::UnitY, rotation); }

	/*
	@fn Tagのgetter関数
	@brief オブジェクトを識別するTagを取得
	@return Tag オブジェクトを識別するTag
	*/
	Tag GetTag() const { return tag; }
	
	/*
	@fn myObjectId変数のgetter関数
	@brief それぞれのオブジェクトが持つIDの取得
	@return int myObjectId それぞれのオブジェクトが持つID
	*/
	int GetObjectId() { return myObjectId; };

	/*
	@fn gameObjectId変数のgetter関数
	@brief 全オブジェクト総数を確認するためのトータルIDの取得
	@return int gameObjectId オブジェクトが生成されるたびに1増えるID
	*/
	static int GetTotalObjectId() { return gameObjectId; };

	/*
	@fn reUseObject変数のgetter関数
	@brief シーンをまたいで利用するかどうかフラグの取得
	@return bool reUseObject シーンをまたいで利用するかどうかフラグ
	*/
	bool GetReUseGameObject() { return reUseObject; }

	/*
	@fn 押し戻し関数(仮想関数)
	@brief 押し戻しを行う
	@param myAABB 自分のAABB
	@param pairAABB 相手のAABB
	@param _pairTag 相手がなんのオブジェクトなのか見る用のTag
	*/
	virtual void FixCollision(const AABB& myAABB, const AABB& pairAABB, const Tag& _pairTag);

	/*
	@fn オブジェクトの回転を計算する関数
	@brief 前方ベクトルを使用してオブジェクトを回転させる
	@param forward 前方ベクトル
	*/
	void RotateToNewForward(const Vector3& forward);

	/*
	@fn 静的なmainCameraを生成する
	*/
	static void CreateMainCamera(const Vector3 _pos);

	/*
	@fn 静的なtitleCameraを生成する
	*/
	static void CreateTitleCamera(const Vector3 _pos);

	/*
	@brief　スイッチ用フラグのgetter
	@return	onFlag
	*/
	bool GetSwitchFlag() { return onFlag; }

	/*
	@brief　tagを使用してGameObjectを探すための関数
	@return	std::vector<GameObject*>を返す
	*/
	static std::vector<GameObject*> FindGameObject(Tag _tag);

	/*
	@brief　使用した全てのGameObjectの削除
	*/
	static 	void RemoveUsedGameObject();

	/*
	@brief　Velocityのgettta関数
	@param	velocity(Vector3型)
	*/
	const Vector3& GetVelocity() const { return velocity; }

	static MainCameraObject* GetMainCamera() { return mainCamera;}

	AABB aabb;

protected:

	std::function<void(GameObject&)> GetOnCollisionFunc() { return std::bind(&GameObject::OnCollision, this, std::placeholders::_1); }
	virtual void OnCollision(const GameObject& _hitObject) {}

	// ゲーム中メインカメラ
	static class MainCameraObject* mainCamera;
	// タイトル画面で使用するカメラ
	static class TitleCameraObject* titleCamera;

	//ゲームオブジェクトの状態
	State state;
	//ゲームオブジェクトのタグ
	Tag tag;
	//ゲームオブジェクトのID、カウント用
	static int gameObjectId;
	//このゲームオブジェクトのID
	const int myObjectId;

	//Transform
	Vector3 position;
	Quaternion rotation;
	Vector3 scale;
	Matrix4 worldTransform;
	Vector3 velocity;
	Vector3 forwardVec;

	//ワールド変換の処理を行う必要性があるか
	bool recomputeWorldTransform;

	//switch用フラグ
	bool onFlag;

	//アタッチされているコンポーネント
	std::vector<class Component*>components;

private:

	/*
	@brief　GameObjectの追加
	@param	追加するGameObjectのポインタ
	*/
	static void AddGameObject(GameObject* _object);
	/*
	@brief　GameObjectの削除
	@param	削除するGameObjectのポインタ
	*/
	static void RemoveGameObject(GameObject* _object);


	//シーンを跨ぐ際に開放されるオブジェクトかどうか、カメラなどが対象になる
	bool reUseObject;
	static std::vector<GameObject*> pendingGameObjects;
	static std::unordered_map<Tag, std::vector<GameObject*>> gameObjectMap;
	static bool updatingGameObject;

	/*
	@brief  ゲームオブジェクトのアップデート処理
	*/
	friend void UpdateGameObjects(float _deltaTime);

	/*
	@brief  ゲームオブジェクトの入力処理
	*/
	friend void ProcessInputs(const InputState & _state);

};

