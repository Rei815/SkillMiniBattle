
#include "bullet.h"
#include "..\..\..\..\utility\utility.h"
#include "../../launcher/launcher.h"
#include "../../unit_manager/unit_manager.h"
#include "../../../../component/model_component/model_component.h"
#include "../../../../component/transform_component/transform_component.h"
const float           IBullet::m_life_time = 4.0f;

/*
 *  �R���X�g���N�^
 */
IBullet::IBullet(COLLIDER_ID collider_id)
    : m_Category(UNIT_CATEGORY::UNKNOWN)
    , m_Velocity(CVector3(CVector3::ZERO))
    , m_Color(0xffffffff)
    , m_LifeTimer(0)
    , m_ColliderID(collider_id)
    , m_Power(1.0f)
    , m_BulletID(BULLET_ID::NONE)
{
}

/*
 *  �f�X�g���N�^
 */
IBullet::~IBullet(void)
{
}

/*
 *  ������
 */
void IBullet::Initialize(UNIT_CATEGORY category, CShot::BulletParameters* bulletParams, const CVector3& position, const CVector3& direction)
{
    m_Category = category;
    m_Velocity = direction * bulletParams->speed;
    m_Color = (category == UNIT_CATEGORY::PLAYER ? m_player_color : m_enemy_color);
    m_GameObject = std::make_shared<CGameObject>();
    m_GameObject->AddComponent<ModelComponent>(MODEL_ID::BULLET);

    // TransformComponent���擾���A�����ݒ���s��
    if (auto transform = m_GameObject->GetComponent<TransformComponent>())
    {
        transform->SetPosition(position);
        m_TransformComponent = transform;
    }
    m_LifeTimer.SetUp(m_life_time);
}

void IBullet::Initialize(UNIT_CATEGORY category, const CVector3& position, const CVector3& direction)
{
    m_Category = category;
    m_Velocity = direction;
    m_Color = (category == UNIT_CATEGORY::PLAYER ? m_player_color : m_enemy_color);
    m_GameObject = std::make_shared<CGameObject>();
    /*���f���R���|�[�l���g�͎��g�Őݒ�*/

    //null�`�F�b�N
    assert(m_TransformComponent != nullptr && "IBullet requires a TransformComponent, but it was not found!");

    // TransformComponent���擾���A�����ݒ���s��
    if (auto transform = m_GameObject->GetComponent<TransformComponent>())
    {
        transform->SetPosition(position);
        m_TransformComponent = transform;
    }

    m_LifeTimer.SetUp(m_life_time);

}

/*
 *  �X�V
 */
void IBullet::Update(void)
{
    m_LifeTimer.Update();

    m_TransformComponent->Translate(m_Velocity);

    if (m_LifeTimer.Finished())
    {
        Delete();
    }
    m_GameObject->Update(vivid::GetDeltaTime());
}

/*
 *  �`��
 */
void IBullet::Draw(void)
{
    if (!m_GameObject || !IsActive()) return;
    // �`��́y�́z�Ɋۓ���
    m_GameObject->Draw();
}

/*
 *  �ʒu�擾
 */
CVector3 IBullet::GetPosition(void)
{
    if (auto transform = m_GameObject->GetComponent<TransformComponent>()) {
        return transform->GetPosition();
    }
    return CVector3::ZERO;
}

/*
 *  ���x�x�N�g���擾
 */
CVector3 IBullet::GetVelocity(void)
{
    return m_Velocity;
}

/*
 *  ���x�x�N�g���ݒ�
 */
void IBullet::SetVelocity(const CVector3& velocity)
{
    m_Velocity = velocity;
}

/*
 *  �A�N�e�B�u�t���O�擾
 */
bool IBullet::IsActive(void)
{
    return m_GameObject ? m_GameObject->IsActive() : false;
}

/*
 *  �A�N�e�B�u�t���O�擾
 */
void IBullet::Delete()
{
    m_GameObject->Delete();
}

/*
 *  ���j�b�g���ʎq�擾
 */
UNIT_CATEGORY IBullet::GetBulletCategory(void)
{
    return m_Category;
}

/*
 *  �e�̐F�擾
 */
unsigned int IBullet::GetBulletColor(void)
{
    return m_Color;
}

COLLIDER_ID IBullet::GetColliderID(void)
{
    return m_ColliderID;
}

float IBullet::GetPower()
{
    return m_Power;
}

BULLET_ID IBullet::GetID()
{
    return m_BulletID;
}

float IBullet::GetRadius()
{
    // �L���b�V�����Ă�����TransformComponent�ɖ₢���킹��
    if (m_TransformComponent)
    {
        // TransformComponent������scale��x�������A�e�̔��a�Ƃ��ĕԂ�
        // ���Ȃ̂ŁAx,y,z�͓���
        return m_TransformComponent->GetScale().x;
    }
    return 0.0f;
}

int IBullet::GetModelHandle(void) const
{
    if (!m_GameObject)
    {
        return VIVID_DX_ERROR;
    }

    // ModelComponent�͂قڕK�����݂���͂������A�O�̂���null�`�F�b�N���s��
    if (auto modelComp = m_GameObject->GetComponent<ModelComponent>())
    {
        return modelComp->GetModelHandle();
    }

    return VIVID_DX_ERROR;
}
