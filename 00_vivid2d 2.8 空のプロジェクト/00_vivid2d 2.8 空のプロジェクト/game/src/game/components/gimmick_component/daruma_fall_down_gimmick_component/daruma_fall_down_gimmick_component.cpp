#include "daruma_fall_down_gimmick_component.h"
#include "daruma_fall_down_gimmick/daruma_fall_down_gimmick.h" // ���̃N���X�̃w�b�_�[

DarumaFallDownGimmickComponent::DarumaFallDownGimmickComponent()
{
    // �R���X�g���N�^�ŁA���̃��W�b�N�N���X�𐶐�
    m_GimmickLogic = std::make_unique<CDarumaFallDownGimmick>();
}

DarumaFallDownGimmickComponent::~DarumaFallDownGimmickComponent() = default;

void DarumaFallDownGimmickComponent::OnAttach(CGameObject* owner)
{
    // ���̃N���X�ɁA�������N�ɃA�^�b�`���ꂽ��������
    m_GimmickLogic->Initialize(owner);
}

void DarumaFallDownGimmickComponent::Update(float delta_time, CGameObject* owner)
{
    // ���t���[���A���̃N���X��Update���Ăяo������
    m_GimmickLogic->Update();
}

void DarumaFallDownGimmickComponent::OgreControlTurn()
{
	// ���̃N���X�̃��\�b�h���Ăяo��
	m_GimmickLogic->OgreControlTurn();
}
