
#include "bullet.h"
#include "../../launcher/launcher.h"
#include "../../../components/model_component/model_component.h"
#include "../../../components/transform_component/transform_component.h"
#include <engine/components/collider_component/mesh_collider_component/mesh_collider_component.h>
const float           IBullet::m_life_time = 4.0f;

/*
 *  コンストラクタ
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
 *  デストラクタ
 */
IBullet::~IBullet(void)
{
}

/*
 *  初期化
 */
void IBullet::Initialize(FACTION_CATEGORY category, CShot::BulletParameters* bulletParams, const CVector3& position, const CVector3& direction)
{
    m_Velocity = direction * bulletParams->speed;
    m_GameObject = std::make_shared<CGameObject>();
    m_GameObject->AddComponent<ModelComponent>(MODEL_ID::BULLET, true);
    m_GameObject->AddComponent<MeshColliderComponent>();
    m_Category = category;
	m_Radius = bulletParams->radius;
    // TransformComponentを取得し、初期設定を行う
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

    /*モデルコンポーネントは自身で設定*/

    //nullチェック
    assert(m_TransformComponent != nullptr && "IBullet requires a TransformComponent, but it was not found!");

    // TransformComponentを取得し、初期設定を行う
    if (auto transform = m_GameObject->GetComponent<TransformComponent>())
    {
        transform->SetPosition(position);
        m_TransformComponent = transform;
    }

    m_LifeTimer.SetUp(m_life_time);

}

/*
 *  更新
 */
void IBullet::Update(void)
{
    m_LifeTimer.Update();

    // 経過時間を取得
    float deltaTime = vivid::GetDeltaTime();

    m_TransformComponent->Translate(m_Velocity * deltaTime);

    if (m_LifeTimer.Finished())
    {
        Delete();
    }
    m_GameObject->Update(deltaTime);
}

/*
 *  描画
 */
void IBullet::Draw(void)
{
    if (!m_GameObject || !IsActive()) return;
    // 描画は【体】に丸投げ
    m_GameObject->Draw();
}

/*
 *  位置取得
 */
CVector3 IBullet::GetPosition(void)
{
    if (auto transform = m_GameObject->GetComponent<TransformComponent>()) {
        return transform->GetPosition();
    }
    return CVector3::ZERO;
}

/*
 *  速度ベクトル取得
 */
CVector3 IBullet::GetVelocity(void)
{
    return m_Velocity;
}

/*
 *  速度ベクトル設定
 */
void IBullet::SetVelocity(const CVector3& velocity)
{
    m_Velocity = velocity;
}

/*
 *  アクティブフラグ取得
 */
bool IBullet::IsActive(void)
{
    return m_GameObject ? m_GameObject->IsActive() : false;
}

/*
 *  アクティブフラグ取得
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
 *  弾の色取得
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

    // ModelComponentはほぼ必ず存在するはずだが、念のためnullチェックを行う
    if (auto modelComp = m_GameObject->GetComponent<ModelComponent>())
    {
        return modelComp->GetHandle();
    }

    return VIVID_DX_ERROR;
}
