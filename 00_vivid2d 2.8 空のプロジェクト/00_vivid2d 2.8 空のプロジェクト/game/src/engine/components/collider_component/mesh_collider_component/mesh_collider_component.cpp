#include "mesh_collider_component.h"
#include "../../../game_manager/game_object/game_object.h"
#include "../../model_component/model_component.h" // ModelComponent����n���h�������炤
#include <DxLib.h>

MeshColliderComponent::MeshColliderComponent()
    : m_ModelHandle(-1) // DxLib�̃n���h����-1�ŏ���������̂���ʓI
{
}

void MeshColliderComponent::OnAttach(CGameObject* owner)
{
    // ���������L���Ă���GameObject�ɃA�^�b�`����Ă���ModelComponent��T��
    auto modelComp = owner->GetComponent<ModelComponent>();
    if (modelComp)
    {
        // ModelComponent������������A�������烂�f���n���h�����擾���ĕێ�����
        m_ModelHandle = modelComp->GetModelHandle();

        // ����CModel�ɂ����������蔻��p�̃Z�b�g�A�b�v�������Ɏ����Ă���
        if (m_ModelHandle != -1)
        {
            MV1SetupCollInfo(m_ModelHandle, -1, 8, 8, 8);
        }
    }
    else
    {
        // ModelComponent���Ȃ��Ɠ��삵�Ȃ��̂ŁA�x�����o���Ȃ�
        // DX_LOGPRINTF("�x��: MeshColliderComponent��ModelComponent��K�v�Ƃ��܂��B");
    }
}

bool MeshColliderComponent::CheckHitLine(
    const CVector3& startPos,
    const CVector3& endPos,
    CVector3& out_hitPosition) const
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
        out_hitPosition = hitPoly.HitPosition;
        return true;
    }

    // �q�b�g���Ȃ������ꍇ
    return false;
}