#pragma once
#include "../collider_component.h"
class CGameObject;
class MeshColliderComponent : public ColliderComponent
{
public:
    MeshColliderComponent();
    ~MeshColliderComponent() = default;

    void OnAttach(CGameObject* owner) override;

    // --- ColliderComponentからのオーバーライド ---
    bool CheckHitLine(
        const CVector3& startPos,
        const CVector3& endPos,
        CVector3& out_hitPosition) const override;

private:
    int m_ModelHandle; // 当たり判定に使用するモデルのハンドル
};