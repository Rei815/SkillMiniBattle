#include "shock_wave_bullet.h"
#include "../../../../components/model_component/model_component.h"
#include "../../../../components/transform_component/transform_component.h"
#include "../../../../components/collider_component/mesh_collider_component/mesh_collider_component.h"

const float CShockWaveBullet::m_max_speed = 50.0f;
const float CShockWaveBullet::m_spread_speed = 8.0f;
const float CShockWaveBullet::m_height = 21.0f;
const float CShockWaveBullet::m_life_time = 1.0f;
const float CShockWaveBullet::m_acceleration = 0.2f;
const float CShockWaveBullet::m_scale = 0.5f;
const float CShockWaveBullet::m_power = 0.5f;
// コンストラクタ：親クラスのデフォルトコンストラクタを呼ぶだけでOK
CShockWaveBullet::CShockWaveBullet()
    : IBullet(COLLIDER_ID::MODEL)
{
}

void CShockWaveBullet::Initialize(FACTION_CATEGORY category, const CVector3& position, const CVector3& direction)
{
    IBullet::Initialize(category, position, direction);
    m_BulletID = BULLET_ID::SHOCK_WAVE;
    AddComponent<ModelComponent>(MODEL_ID::STOMP_COLL);
    AddComponent<MeshColliderComponent>();

    m_SpreadSpeed = m_spread_speed;
    m_CurrentScale = m_scale;
}

void CShockWaveBullet::Update()
{
    IBullet::Update();

    // アクティブでなければ、何もしない
    if (!IsActive()) return;

    // --- 衝撃波独自の更新処理 ---
    m_SpreadSpeed += m_acceleration; // 加速
    m_CurrentScale += m_SpreadSpeed * vivid::GetDeltaTime();

    if (m_TransformComponent)
    {
        m_TransformComponent->SetScale(CVector3(m_CurrentScale, 1.0f, m_CurrentScale)); // 縦方向には広げない
    }
}
