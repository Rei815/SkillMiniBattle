
#include "bullet.h"
#include "../../launcher/launcher.h"
#include "../../../components/model_component/model_component.h"
#include "../../../components/transform_component/transform_component.h"
#include <engine/components/collider_component/mesh_collider_component/mesh_collider_component.h>
const float           IBullet::m_life_time = 4.0f;
const DxLib::COLOR_F IBullet::m_color = DxLib::COLOR_F{ 0.8f, 0.0f, 0.0f, 1.0f };
/*
 *  �R���X�g���N�^
 */
IBullet::IBullet(COLLIDER_ID collider_id)
    : m_Velocity(CVector3(CVector3::ZERO))
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
    auto model = AddComponent<ModelComponent>(MODEL_ID::BULLET, true);
    model->SetMaterialColor(0, m_color);

	//���b�V���R���|�[�l���g��ǉ�
    AddComponent<MeshColliderComponent>();
    m_Category = category;
	m_Radius = bulletParams->radius;
    // TransformComponent���擾���A�����ݒ���s��
    if (auto transform = GetComponent<TransformComponent>())
    {
        transform->SetPosition(position);
        m_TransformComponent = transform;
    }
    m_LifeTimer.SetUp(m_life_time);
}

void IBullet::Initialize(FACTION_CATEGORY category, const CVector3& position, const CVector3& direction)
{
    m_Velocity = direction;
    m_Category = category;
	m_TransformComponent = GetComponent<TransformComponent>();
    /*���f���R���|�[�l���g�͎��g�Őݒ�*/

    // TransformComponent���擾���A�����ݒ���s��
    if (auto transform = GetComponent<TransformComponent>())
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
	CGameObject::Update(deltaTime);  
}

/*
 *  �`��
 */
void IBullet::Draw(void)
{
    if (!IsActive()) return;
	CGameObject::Draw();
}

/*
 *  �ʒu�擾
 */
CVector3 IBullet::GetPosition(void)
{
    if (m_TransformComponent)
    {
        return m_TransformComponent->GetPosition();
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
    return m_IsActive;
}

/*
 *  �A�N�e�B�u�t���O�擾
 */
void IBullet::Delete()
{
    m_IsActive = false;
}

FACTION_CATEGORY IBullet::GetBulletCategory(void)
{
    return m_Category;
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
    // ModelComponent�͂قڕK�����݂���͂������A�O�̂���null�`�F�b�N���s��
    if (auto modelComp = GetComponent<ModelComponent>())
    {
        return modelComp->GetHandle();
    }

    return VIVID_DX_ERROR;
}
