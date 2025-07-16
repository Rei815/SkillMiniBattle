#include "mesh_collider_component.h"
#include "../../../core/game_object/game_object.h"
#include "../../model_component/model_component.h" // ModelComponent����n���h�������炤
#include "../../transform_component/transform_component.h" // ModelComponent����n���h�������炤
MeshColliderComponent::MeshColliderComponent()
    : m_ModelHandle(-1) // DxLib�̃n���h����-1�ŏ���������̂���ʓI
{
}

void MeshColliderComponent::OnAttach(CGameObject* owner)
{
    m_Owner = owner; // �I�[�i�[��ۑ�
    // ���������L���Ă���GameObject�ɃA�^�b�`����Ă���ModelComponent��T��
    auto modelComp = owner->GetComponent<ModelComponent>();
    if (modelComp)
    {
        // ModelComponent������������A�������烂�f���n���h�����擾���ĕێ�����
        m_ModelHandle = modelComp->GetHandle();

        // ����CModel�ɂ����������蔻��p�̃Z�b�g�A�b�v�������Ɏ����Ă���
        if (m_ModelHandle != -1)
        {
            DxLib::MV1SetupCollInfo(m_ModelHandle, -1, 8, 8, 8);
        }
    }
    else
    {
        // ModelComponent���Ȃ��Ɠ��삵�Ȃ��̂ŁA�x�����o���Ȃ�
        // DX_LOGPRINTF("�x��: MeshColliderComponent��ModelComponent��K�v�Ƃ��܂��B");
    }
}

void MeshColliderComponent::Update(float delta_time, CGameObject* owner)
{
	m_ModelHandle = owner->GetComponent<ModelComponent>()->GetHandle(); // ModelComponent����n���h�����擾
    DxLib::MV1RefreshCollInfo(m_ModelHandle, -1, -1); // ��2������-1��ǉ�����ƁA�����S�ł�
}

bool MeshColliderComponent::CheckHitLine(const CVector3& startPos,const CVector3& endPos, CollisionResult& out_result) const
{
    if (m_ModelHandle == -1)
    {
        return false; // �n���h���������Ȃ牽�����Ȃ�
    }

    // DX���C�u�����̓����蔻��֐����Ăяo��
    MV1_COLL_RESULT_POLY hitPoly = MV1CollCheck_Line(m_ModelHandle, -1, startPos, endPos);

    if (hitPoly.HitFlag) // DxLib��HitFlag��int�^ (0 or 1)
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
    DxLib::MV1_COLL_RESULT_POLY_DIM hitResult = MV1CollCheck_Sphere(m_ModelHandle, -1, center, radius);
    // �q�b�g�������ǂ����� bool �ɕϊ�
    out_result.isHit = (hitResult.HitNum > 0);

    if (out_result.isHit)
    {
        // �q�b�g�����ꍇ�A�ڍ׏����\���̂Ɋi�[����
        out_result.hitPosition = hitResult.Dim->HitPosition;
        out_result.hitNormal = hitResult.Dim->Normal;
        MV1CollResultPolyDimTerminate(hitResult); // ��n��
        return true;

    }
    // �q�b�g���Ȃ������ꍇ
    return false;

}

bool MeshColliderComponent::CheckHitCapsule(const CVector3& posA, const CVector3& posB, float radius ,CVector3& out_hitPosition) const
{
    if (m_ModelHandle == -1) return false;

    // ���f���ƃJ�v�Z���̓����蔻��
    DxLib::MV1_COLL_RESULT_POLY_DIM hitResult = MV1CollCheck_Capsule(m_ModelHandle, -1, posA, posB, radius);
    if (hitResult.HitNum > 0)
    {
        // �q�b�g�����ꍇ�A�Փˈʒu��out�����Ɋi�[����true��Ԃ�
        out_hitPosition = hitResult.Dim->HitPosition;

        MV1CollResultPolyDimTerminate(hitResult); // ��n��
        return true;

    }
    // �q�b�g���Ȃ������ꍇ
    return false;
}