#pragma once
#include "../collider_component.h"
class CGameObject;
class MeshColliderComponent : public ColliderComponent
{
public:
    MeshColliderComponent();
    ~MeshColliderComponent() = default;

    void OnAttach(CGameObject* owner) override;

    // �Փˈʒu���s�v�ȏꍇ�͂�������Ă�
    bool CheckHitLine(const CVector3& startPos, const CVector3& endPos) const;

    bool CheckHitLine(const CVector3& startPos, const CVector3& endPos, CVector3& out_hitPosition) const override;

    // �w�肳�ꂽ�u���v�Ǝ������������Ă��邩�H
    bool CheckHitSphere(const CVector3& center, float radius, CollisionResult& out_result) const override;

    // �w�肳�ꂽ�u�J�v�Z���v�Ǝ������������Ă��邩�H
    bool CheckHitCapsule(const CVector3& posA, const CVector3& posB, float radius, CVector3& out_hitPosition) const override;

private:
    int m_ModelHandle; // �����蔻��Ɏg�p���郂�f���̃n���h��
};