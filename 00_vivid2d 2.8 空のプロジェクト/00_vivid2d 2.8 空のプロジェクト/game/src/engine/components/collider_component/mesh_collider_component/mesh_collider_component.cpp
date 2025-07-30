#include "mesh_collider_component.h"
#include "../../../core/game_object/game_object.h"
#include "../../model_component/model_component.h"
#include "../../transform_component/transform_component.h"
MeshColliderComponent::MeshColliderComponent()
    : m_ModelHandle(-1)
{
}

void MeshColliderComponent::OnAttach(CGameObject* owner)
{
    m_Owner = owner;
    auto modelComp = owner->GetComponent<ModelComponent>();
    if (modelComp)
    {

        m_ModelHandle = modelComp->GetHandle();

        if (m_ModelHandle != -1)
        {
			// ���f���̓����蔻����Z�b�g�A�b�v
            DxLib::MV1SetupCollInfo(m_ModelHandle, -1, 8, 8, 8);
        }
    }
}

void MeshColliderComponent::Update(float delta_time, CGameObject* owner)
{
    if (m_ModelHandle == -1) return;
    DxLib::MV1RefreshCollInfo(m_ModelHandle);
}

bool MeshColliderComponent::CheckHitLine(const CVector3& startPos,const CVector3& endPos, CollisionResult& out_result) const
{
    if (m_ModelHandle == -1)
    {
        return false;
    }

	// ���f���Ɛ����̓����蔻��
    MV1_COLL_RESULT_POLY hitPoly = DxLib::MV1CollCheck_Line(m_ModelHandle, -1, startPos, endPos);

    if (hitPoly.HitFlag)
    {
        // �q�b�g�����ꍇ�A�Փˈʒu��out�����Ɋi�[����true��Ԃ�
        out_result.hitPosition = hitPoly.HitPosition;
        out_result.hitNormal = hitPoly.Normal;
        return true;
    }

	// �q�b�g���Ȃ������ꍇ
    return false;
}
bool MeshColliderComponent::CheckHitSphere(const CVector3& center, float radius, CollisionResult& out_result) const
{
    if (m_ModelHandle == -1) return false;

	// ���f���Ƌ��̓����蔻��
    DxLib::MV1_COLL_RESULT_POLY_DIM hitResult = DxLib::MV1CollCheck_Sphere(m_ModelHandle, -1, center, radius);
    // �q�b�g�������ǂ����� bool �ɕϊ�
    out_result.isHit = (hitResult.HitNum > 0);

    if (out_result.isHit)
    {
        // �q�b�g�����ꍇ�A�ڍ׏����\���̂Ɋi�[����
        out_result.hitPosition = hitResult.Dim->HitPosition;
        out_result.hitNormal = hitResult.Dim->Normal;

        // ��n��
        MV1CollResultPolyDimTerminate(hitResult); 
        return true;

    }
    // �q�b�g���Ȃ������ꍇ
    return false;

}

bool MeshColliderComponent::CheckHitCapsule(const CVector3& posA, const CVector3& posB, float radius ,CVector3& out_hitPosition) const
{
    if (m_ModelHandle == -1) return false;

    // ���f���ƃJ�v�Z���̓����蔻��
    DxLib::MV1_COLL_RESULT_POLY_DIM hitResult = DxLib::MV1CollCheck_Capsule(m_ModelHandle, -1, posA, posB, radius);
    if (hitResult.HitNum > 0)
    {
        // �q�b�g�����ꍇ�A�Փˈʒu��out�����Ɋi�[����true��Ԃ�
        out_hitPosition = hitResult.Dim->HitPosition;

        // ��n��
        MV1CollResultPolyDimTerminate(hitResult); 
        return true;

    }
    // �q�b�g���Ȃ������ꍇ
    return false;
}