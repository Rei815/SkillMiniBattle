
#include "bullet.h"
#include "..\..\..\..\utility\utility.h"
#include "../../launcher/launcher.h"
#include "../../unit_manager/unit_manager.h"
#include "../../../../component/model_component/model_component.h"
#include "../../../../component/transform_component/transform_component.h"
const float           IBullet::m_life_time = 4.0f;

/*
 *  コンストラクタ
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
 *  デストラクタ
 */
IBullet::~IBullet(void)
{
}

/*
 *  初期化
 */
void IBullet::Initialize(UNIT_CATEGORY category, CShot::BulletParameters* bulletParams, const CVector3& position, const CVector3& direction)
{
    m_Category = category;
    m_Velocity = direction * bulletParams->speed;
    m_Color = (category == UNIT_CATEGORY::PLAYER ? m_player_color : m_enemy_color);
    m_GameObject = std::make_shared<CGameObject>();
    m_GameObject->AddComponent<ModelComponent>(MODEL_ID::BULLET);

    // TransformComponentを取得し、初期設定を行う
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

    m_TransformComponent->Translate(m_Velocity);

    if (m_LifeTimer.Finished())
    {
        Delete();
    }
    m_GameObject->Update(vivid::GetDeltaTime());
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

/*
 *  ユニット識別子取得
 */
UNIT_CATEGORY IBullet::GetBulletCategory(void)
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
    // キャッシュしておいたTransformComponentに問い合わせる
    if (m_TransformComponent)
    {
        // TransformComponentが持つscaleのx成分を、弾の半径として返す
        // 球なので、x,y,zは同じ
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

    // ModelComponentはほぼ必ず存在するはずだが、念のためnullチェックを行う
    if (auto modelComp = m_GameObject->GetComponent<ModelComponent>())
    {
        return modelComp->GetModelHandle();
    }

    return VIVID_DX_ERROR;
}
