#include "shock_wave_bullet.h"
#include "../../../../../component/transform_component/transform_component.h"
#include "../../../../../component/model_component/model_component.h"

const float CShockWaveBullet::m_max_speed = 50.0f;
const float CShockWaveBullet::m_spread_speed = 8.0f;
const float CShockWaveBullet::m_height = 21.0f;
const float CShockWaveBullet::m_life_time = 1.0f;
const float CShockWaveBullet::m_acceleration = 0.2f;
const float CShockWaveBullet::m_scale = 0.5f;
const float CShockWaveBullet::m_power = 0.5f;
// �R���X�g���N�^�F�e�N���X�̃f�t�H���g�R���X�g���N�^���ĂԂ�����OK
CShockWaveBullet::CShockWaveBullet()
    : IBullet(COLLIDER_ID::MODEL)
{
}

void CShockWaveBullet::Initialize(UNIT_CATEGORY category, const CVector3& position, const CVector3& direction)
{
    IBullet::Initialize(category, position, direction);
    m_BulletID = BULLET_ID::SHOCK_WAVE;
    m_GameObject->AddComponent<ModelComponent>(MODEL_ID::STOMP_COLL);

    m_SpreadSpeed = m_spread_speed;
    m_CurrentScale = m_scale;
}

void CShockWaveBullet::Update()
{
    IBullet::Update();

    // �A�N�e�B�u�łȂ���΁A�������Ȃ�
    if (!IsActive()) return;

    // --- �Ռ��g�Ǝ��̍X�V���� ---
    m_SpreadSpeed += m_acceleration; // ����
    m_CurrentScale += m_SpreadSpeed * vivid::GetDeltaTime();

    if (m_TransformComponent)
    {
        m_TransformComponent->SetScale(CVector3(m_CurrentScale, 1.0f, m_CurrentScale)); // �c�����ɂ͍L���Ȃ�
    }
}
