#include "dodge_ball_gimmick_component.h"
#include "dodge_ball_gimmick/dodge_ball_gimmick.h" // ���̃N���X�̃w�b�_�[

DodgeBallGimmickComponent::DodgeBallGimmickComponent()
{
    // �R���X�g���N�^�ŁA���̃��W�b�N�N���X�𐶐�
    m_GimmickLogic = std::make_unique<CDodgeBallGimmick>();
}

DodgeBallGimmickComponent::~DodgeBallGimmickComponent() = default;

void DodgeBallGimmickComponent::OnAttach(CGameObject* owner)
{
    // ���̃N���X�ɁA�������N�ɃA�^�b�`���ꂽ��������
    m_GimmickLogic->Initialize(owner);
}

void DodgeBallGimmickComponent::Update(float delta_time, CGameObject* owner)
{
    // ���t���[���A���̃N���X��Update���Ăяo������
    m_GimmickLogic->Update();
}

void DodgeBallGimmickComponent::SetOperationFlag(bool flag)
{
    m_GimmickLogic->SetOperationFlag(flag);
}

CANNON_STATE DodgeBallGimmickComponent::GetNowState()
{
    return m_GimmickLogic->GetNowState();
}

bool DodgeBallGimmickComponent::GetShotFlag()
{
    return m_GimmickLogic->GetShotFlag();
}