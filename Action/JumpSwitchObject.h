#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

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
    ~JumpSwitchObject();

    void UpdateGameObject(float _deltaTime)override;

private:

    void OnCollision(const GameObject& _hitObject)override;

    Mesh* mesh;
    MeshComponent* meshComponent;
    BoxCollider* boxCollider;

};
