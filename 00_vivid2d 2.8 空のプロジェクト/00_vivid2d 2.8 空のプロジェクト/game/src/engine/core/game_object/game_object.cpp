#include "game_object.h"
#include "../../component/transform_component/transform_component.h"

CGameObject::CGameObject()
    : m_IsActive(true)
{
    //���W�͕K����������
    AddComponent<TransformComponent>();
}

CGameObject::~CGameObject()
{
    // �}�b�v�̊e�v�f�i�e�R���|�[�l���g�^�j�ɑ΂��ă��[�v
    for (auto const& pair : m_Components)
    {
        // �x�N�^�[�̒��̊e�R���|�[�l���g�C���X�^���X�ɑ΂��ă��[�v
        for (auto& component : pair.second)
        {
            component->OnDetach(this);
        }
    }
}

void CGameObject::Initialize()
{
    // GameObject �S�̂̏��������W�b�N�B
    // �e�R���|�[�l���g�� OnAttach �� AddComponent() �ŌĂяo�����B
    // �����ł́AGameObject ���̂����������������L�q����B
    // �K�v�ł���΁A�A�^�b�`����Ă���S�ẴR���|�[�l���g��Initialize���\�b�h���Ăяo�����Ƃ��ł��邪�A
    // OnAttach �ōς܂�����ꍇ�͕s�v�B
}

void CGameObject::Update(float delta_time)
{
    if (!m_IsActive)
    {
        return;
    }

    // �A�^�b�`����Ă���S�ẴR���|�[�l���g�� Update ���Ăяo��
    // ����̓V���v���Ȏ����ł���A�����I�ɂ̓V�X�e���ɂ��X�V���f���Ɉڍs���邱�Ƃ���������
    for (auto const& pair : m_Components)
    {
        for (auto& component : pair.second)
        {
            component->Update(delta_time, this); // GameObject* this ��n��

        }
    }
}

void CGameObject::Draw() 
{
    if (!m_IsActive)
    {
        return;
    }
    // �`��֘A�̃R���|�[�l���g������΁A����Draw���\�b�h���Ăяo���Ȃ�
    // ��: if (auto renderComp = GetComponent<RenderComponent>()) { renderComp->Draw(this); }
}

void CGameObject::Finalize()
{
    // GameObject �S�̂̏I�������B
    // �R���|�[�l���g�� OnDetach �̓f�X�g���N�^�ŌĂ΂�邽�߁A�����ł͒ǉ��̏������L�q
}