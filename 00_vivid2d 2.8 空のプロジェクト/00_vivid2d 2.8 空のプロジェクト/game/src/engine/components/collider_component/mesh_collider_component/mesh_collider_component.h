#pragma once
#include "../collider_component.h"
class CGameObject;
class MeshColliderComponent : public ColliderComponent
{
public:
    MeshColliderComponent();
    ~MeshColliderComponent() = default;

    void OnAttach(CGameObject* owner) override;

	void Update(float delta_time, CGameObject* owner) override;
    // 衝突位置が不要な場合はこちらを呼ぶ
    bool CheckHitLine(const CVector3& startPos, const CVector3& endPos) const;

    bool CheckHitLine(const CVector3& startPos, const CVector3& endPos, CVector3& out_hitPosition) const override;

    // 指定された「球」と自分が当たっているか？
    bool CheckHitSphere(const CVector3& center, float radius, CollisionResult& out_result) const override;

    // 指定された「カプセル」と自分が当たっているか？
    bool CheckHitCapsule(const CVector3& posA, const CVector3& posB, float radius, CVector3& out_hitPosition) const override;

private:
    int m_ModelHandle; // 当たり判定に使用するモデルのハンドル
};