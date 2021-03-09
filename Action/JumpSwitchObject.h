#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

/*
@file JumpSwitchObject.h
@brief JumpSwitchの生成と更新を行う
*/
class JumpSwitchObject :
    public GameObject
{

public:

    /*
    @fn コンストラクタ
    @param	ポジション
    @param	objectのサイズ
    @param	オブジェクト判別用tag
    */
    JumpSwitchObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag);
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~JumpSwitchObject();
    
    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    
    /*
    @fn 当たり判定が行われHitした際に呼ばれる関数
    @param	当たったGameObject
    */
    void OnCollision(const GameObject& _hitObject)override;
    // 3Dモデルの描画を行うクラス
    Mesh* mesh;
    MeshComponent* meshComponent;
    // 当たり判定を行うクラス
    BoxCollider* boxCollider;

};
