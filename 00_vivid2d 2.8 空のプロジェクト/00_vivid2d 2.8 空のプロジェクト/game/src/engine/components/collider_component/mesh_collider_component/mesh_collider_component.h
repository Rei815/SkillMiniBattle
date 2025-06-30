#pragma once
#include "../collider_component.h"
class CGameObject;
class MeshColliderComponent : public ColliderComponent
{
public:
    MeshColliderComponent();
    ~MeshColliderComponent() = default;

    void OnAttach(CGameObject* owner) override;

    // --- ColliderComponent����̃I�[�o�[���C�h ---
    bool CheckHitLine(
        const CVector3& startPos,
        const CVector3& endPos,
        CVector3& out_hitPosition) const override;

private:
    int m_ModelHandle; // �����蔻��Ɏg�p���郂�f���̃n���h��
};