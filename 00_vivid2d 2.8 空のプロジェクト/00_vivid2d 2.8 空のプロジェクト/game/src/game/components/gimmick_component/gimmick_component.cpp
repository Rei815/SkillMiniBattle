#include "gimmick_component.h" // �Ή�����w�b�_�[�t�@�C��
#include "../../../engine/core/game_object/game_object.h"

GimmickComponent::GimmickComponent()
    : m_State(GIMMICK_STATE::WAIT)
    , m_Timer()
{
    // IComponent�̃R���X�g���N�^�� m_IsActive �� true �ɏ����������z��
}

void GimmickComponent::Update(float delta_time, CGameObject* owner)
{
    // �h���N���X�� Update ����������Ă��^�C�}�[�͋��ʂōX�V�������ꍇ�A
    // �h���N���X�� Update �̐擪�� GimmickComponent::Update(delta_time, owner); ���Ă�
    m_Timer.Update(); // ����CTimer��delta_time�������Ɏ��Ȃ��ꍇ
    // m_Timer.Update(delta_time); // delta_time�ōX�V����ꍇ
}

GIMMICK_STATE GimmickComponent::GetState() const
{
    return m_State;
}

void GimmickComponent::SetState(GIMMICK_STATE state)
{
    m_State = state;
}

void GimmickComponent::SetTimer(float time)
{
    m_Timer.SetUp(time);
}
