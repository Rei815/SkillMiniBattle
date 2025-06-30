#include "fall_gimmick_component.h" // �Ή�����w�b�_�[�t�@�C��
#include "../../../../engine/components/transform_component/transform_component.h"
#include "../../../../engine/components/model_component/model_component.h"
#include "../../../../engine/core/game_object/game_object.h"
#include "../../../../engine/components/collider_component/collider_component.h"

const	float				FallGimmickComponent::m_fall_speed = 5.0f;
const	float				FallGimmickComponent::m_return_height = -500.0f;
const	float				FallGimmickComponent::m_return_time = 3.0f;

FallGimmickComponent::FallGimmickComponent()
    : GimmickComponent()
    , m_ReturnTime(m_return_time)
    , m_StartHeight(0.0f)
    , m_ReturnTimer(m_return_time)
{
}

void FallGimmickComponent::OnAttach(CGameObject* owner)
{
    // ���̃R���|�[�l���g���A�^�b�`���ꂽ���Ɉ�x�����Ă΂�鏉��������

    // ������ TransformComponent ���擾���āA�����̍�����ۑ�����
    auto transform = owner->GetComponent<TransformComponent>();
    if (transform)
    {
        m_StartHeight = transform->GetPosition().y;
    }

    // �e�^�C�}�[���Z�b�g�A�b�v
    m_Timer.SetUp(m_ReturnTime);
    m_ReturnTimer.SetUp(m_ReturnTime);
}

void FallGimmickComponent::Update(float delta_time, CGameObject* owner)
{
    // ���t���[���Ă΂��X�V����

    // �܂��e�N���X�̋��ʏ����i�^�C�}�[�X�V�Ȃǁj���Ă�
    GimmickComponent::Update(delta_time, owner);

    // �A�g����R���|�[�l���g���擾
    auto transform = owner->GetComponent<TransformComponent>();
    auto model = owner->GetComponent<ModelComponent>(); // �����ڂ��Ǘ�����R���|�[�l���g

    // TransformComponent ���Ȃ���Ώ����𒆒f
    if (!transform) { return; }

    CVector3 currentPos = transform->GetPosition();

    switch (m_State)
    {
    case GIMMICK_STATE::WAIT:
        // �ҋ@���͉������Ȃ�
        break;

    case GIMMICK_STATE::PLAY:
        // ��������
        m_Timer.Update();
        if (m_Timer.Finished())
        {
            m_Timer.Reset();
            m_Timer.SetActive(false);

            // �������Ɉړ�������i�t���[�����[�g�Ɉˑ����Ȃ��悤�� delta_time ���|����j
            transform->Translate(CVector3(0.0f, -m_fall_speed * delta_time, 0.0f));
        }

        // �A���t�@�l�i�s�����x�j���v�Z���Č����ڂɔ��f
        if (model)
        {
            float alpha = (currentPos.y - m_return_height) / (m_StartHeight - m_return_height);
            model->SetAlpha(alpha);
        }

        // ����̍����܂ŗ������瓖���蔻��𖳌���
        if (currentPos.y <= (m_StartHeight + m_return_height) * 0.5f)
        {
            if (auto collider = owner->GetComponent<ColliderComponent>()) // �����蔻��R���|�[�l���g
            {
                collider->SetEnabled(false); // �����蔻���OFF�ɂ��郁�\�b�h������Ɖ���
            }
        }

        // ���A�n�_�܂ŗ�������A��Ԃ�FINISH�Ɉڍs
        if (currentPos.y <= m_return_height)
        {
            m_Timer.SetActive(true);
            m_Timer.SetUp(m_ReturnTime);
            m_State = GIMMICK_STATE::FINISH;
        }
        break;

    case GIMMICK_STATE::FINISH:
        // ���A����
        m_ReturnTimer.Update();
        if (m_ReturnTimer.Finished())
        {
            // --- ��Ԃ����ɖ߂� ---
            m_ReturnTimer.Reset();

            // �ʒu�������ʒu�ɖ߂�
            currentPos.y = m_StartHeight;
            transform->SetPosition(currentPos);

            // �����ڂ����ɖ߂�
            if (model)
            {
                model->SetAlpha(1.0f);
            }

            // �����蔻������ɖ߂�
            if (auto collider = owner->GetComponent<ColliderComponent>())
            {
                collider->SetEnabled(true);
            }

            // �ҋ@��Ԃɖ߂�
            m_State = GIMMICK_STATE::WAIT;
        }
        break;
    }
}

void FallGimmickComponent::AddReturnTime(float time)
{
    m_ReturnTime += time;
    m_ReturnTimer.SetUp(m_ReturnTime);
}