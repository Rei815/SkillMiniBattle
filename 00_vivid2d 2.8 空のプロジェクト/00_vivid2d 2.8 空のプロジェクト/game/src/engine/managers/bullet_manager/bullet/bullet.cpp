
#include "bullet.h"
#include "../../launcher/launcher.h"
#include "../../../components/model_component/model_component.h"
#include "../../../components/transform_component/transform_component.h"
#include <engine/components/collider_component/mesh_collider_component/mesh_collider_component.h>
const float           IBullet::m_life_time = 4.0f;

/*
 *  �R���X�g���N�^
 */
IBullet::IBullet(COLLIDER_ID collider_id)
    : m_Velocity(CVector3(CVector3::ZERO))
    , m_Color(0xff0000ff)
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
void IBullet::Initialize(FACTION_CATEGORY category, CShot::BulletParameters* bulletParams, const CVector3& position, const CVector3& direction)
{
    m_Velocity = direction * bulletParams->speed;
    m_GameObject = std::make_shared<CGameObject>();
    m_GameObject->AddComponent<ModelComponent>(MODEL_ID::BULLET, true);
    m_GameObject->AddComponent<MeshColliderComponent>();
    m_Category = category;
	m_Radius = bulletParams->radius;
    // TransformComponent���擾���A�����ݒ���s��
    if (auto transform = m_GameObject->GetComponent<TransformComponent>())
    {
        transform->SetPosition(position);
        m_TransformComponent = transform;
    }
    m_LifeTimer.SetUp(m_life_time);
}

void IBullet::Initialize(FACTION_CATEGORY category, const CVector3& position, const CVector3& direction)
{
    m_Velocity = direction;
    m_GameObject = std::make_shared<CGameObject>();
    m_Category = category;

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

    // �o�ߎ��Ԃ��擾
    float deltaTime = vivid::GetDeltaTime();

    m_TransformComponent->Translate(m_Velocity * deltaTime);

    if (m_LifeTimer.Finished())
    {
        Delete();
    }
    m_GameObject->Update(deltaTime);
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

FACTION_CATEGORY IBullet::GetBulletCategory(void)
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
    return m_Radius;
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
        return modelComp->GetHandle();
    }

    return VIVID_DX_ERROR;
}
