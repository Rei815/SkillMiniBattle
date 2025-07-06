#include "fall_gimmick_component.h"
#include "../../../../engine/components/transform_component/transform_component.h"
#include "../../../../engine/components/model_component/model_component.h"
#include "../../../../engine/core/game_object/game_object.h"
#include "../../../../engine/components/collider_component/mesh_collider_component/mesh_collider_component.h"

const	float				FallGimmickComponent::m_fall_speed = 5.0f;
const	float				FallGimmickComponent::m_return_height = -500.0f;
const	float				FallGimmickComponent::m_return_time = 3.0f;
const	std::string		FallGimmickComponent::m_file_name_list[] = {
    "data\\Models\\Textures\\fall_out_circle.png",
    "data\\Models\\Textures\\fall_out_cross.png",
    "data\\Models\\Textures\\fall_out_moon.png",
    "data\\Models\\Textures\\fall_out_square.png",
    "data\\Models\\Textures\\fall_out_sun.png",
    "data\\Models\\Textures\\fall_out_triangle.png",
};
FallGimmickComponent::FallGimmickComponent(OBJECT_ID id)
    : GimmickComponent()
    , m_ReturnTime(m_return_time)
    , m_StartHeight(0.0f)
    , m_ReturnTimer(m_return_time)
{
    switch (id)
    {
    case OBJECT_ID::FALL_FLOOR_CIRCLE:		m_MarkID = MARK_ID::CIRCLE;		break;
    case OBJECT_ID::FALL_FLOOR_CROSS:		m_MarkID = MARK_ID::CROSS;		break;
    case OBJECT_ID::FALL_FLOOR_MOON:		m_MarkID = MARK_ID::MOON;		break;
    case OBJECT_ID::FALL_FLOOR_SQUARE:		m_MarkID = MARK_ID::SQUARE;		break;
    case OBJECT_ID::FALL_FLOOR_SUN:		    m_MarkID = MARK_ID::SUN;		break;
    case OBJECT_ID::FALL_FLOOR_TRIANGLE:	m_MarkID = MARK_ID::TRIANGLE;	break;
    }

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

    CVector3 rotation = transform->GetRotation();
    switch (m_MarkID)
    {
    case MARK_ID::CIRCLE:   rotation.y = 30; break;
    case MARK_ID::CROSS:    rotation.y = 30; break;
    case MARK_ID::MOON:     rotation.y = 90; break;
    case MARK_ID::SQUARE:   rotation.y = -30;break;
    case MARK_ID::SUN:      rotation.y = 90; break;
    case MARK_ID::TRIANGLE: rotation.y = -30;break;
    case MARK_ID::NONE:
        break;
    }
    transform->SetRotation(rotation);
    // �e�^�C�}�[���Z�b�g�A�b�v
    m_ReturnTimer.SetUp(m_ReturnTime);

    auto FileName = m_file_name_list[static_cast<int>(m_MarkID)];
    vivid::LoadTexture(FileName);

    int grHandle = vivid::core::FindLoadedTexture(FileName);

    auto model = owner->GetComponent<ModelComponent>();
    MV1SetTextureGraphHandle(model->GetHandle(), 0, grHandle, true);

    //���f���𔼓����ɕύX
    DxLib::COLOR_F color = model->GetMaterialColor(0);
    //�A���t�@�l���N���A���A100������
    color.a /= 2;
    model->SetMaterialColor(0, color);
    owner->SetTag(GameObjectTag::FLOOR);
}

void FallGimmickComponent::Update(float delta_time, CGameObject* owner)
{
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
        m_ReturnTimer.Update();
        if (m_ReturnTimer.Finished())
        {
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
            if (auto collider = owner->GetComponent<MeshColliderComponent>()) // �����蔻��R���|�[�l���g
            {
                collider->SetEnabled(false); // �����蔻���OFF�ɂ��郁�\�b�h������Ɖ���
            }
        }

        // ���A�n�_�܂ŗ�������A��Ԃ�FINISH�Ɉڍs
        if (currentPos.y <= m_return_height)
        {
            m_ReturnTimer.SetActive(true);
            m_ReturnTimer.SetUp(m_ReturnTime);
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
            if (auto collider = owner->GetComponent<MeshColliderComponent>())
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