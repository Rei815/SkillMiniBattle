#include "unit.h"
#include "..\..\..\..\utility\utility.h"
#include "..\..\effect_manager\effect_manager.h"
#include "..\..\sound_manager\sound_manager.h"
#include "..\..\camera\camera.h"
#include "../../bullet_manager/bullet/bullet.h"
#include <vivid.cpp>
#include "../unit_manager.h"

const float             IUnit::m_destroy_scale_adjust = 25.0f;
const float             IUnit::m_alpha_speed = 0.025f;
const CVector3          IUnit::m_gravity = CVector3(0.0f, -0.85f, 0.0f);

IUnit::IUnit()
{
}

/*
 *  コンストラクタ
 */
IUnit::
IUnit(UNIT_CATEGORY category, UNIT_ID unit_id)
    : m_Transform(CTransform())
    , m_Velocity(CVector3::ZERO)
    , m_ForwardVector(CVector3::FORWARD)
    , m_AffectedVelocity(CVector3::ZERO)
    , m_ActiveFlag(true)
    , m_Category(category)
    , m_UnitID(unit_id)
    , m_InvincibleFlag(false)
    , m_UnitState(UNIT_STATE::ATTACK)
    , m_Max_Vertex()
    , m_Radius()
    , m_DamageRate(1.0f)
    , m_Shot()
    , m_Alpha()
    , m_DefeatFlag(false)
    , m_Gravity()
    , m_Parent(nullptr)
{
}

/*
 *  デストラクタ
 */
IUnit::
~IUnit(void)
{
}

/*
 *  初期化
 */
void
IUnit::
Initialize(UNIT_ID id, const CVector3& position)
{
    m_UnitID = id;
    m_Transform.position = position;
    m_Velocity = CVector3();
    m_ActiveFlag = true;
    m_InvincibleFlag = false;
    m_UnitState = UNIT_STATE::APPEAR;
    m_Alpha = 0.0f;
    m_RevertAlpha = false;
    m_Gravity = m_gravity;
}
/*
 *  更新
 */
void
IUnit::
Update(void)
{
    if (m_Parent != nullptr)
    {

        //一度接地したらジャンプや判定の外に行かない限り接地したオブジェクトに追従する
        float offset = m_Radius - m_Radius / 3.0f;
        const float line_length = 100.0f;
        bool releaseFlag = false;
        for (int i = 0; i < 9; i++)
        {
            CVector3 start = m_Transform.position + CVector3(-offset + (offset) * (i % 3), 0.0f, -offset + (offset) * (i / 3));
            CVector3 end = start + CVector3(0, -line_length, 0);
            CVector3 hitPos = m_Parent->GetModel().GetHitLinePosition(start, end);
            if (hitPos != end)
            {
                m_Transform.position.y = hitPos.y + m_Radius;
                releaseFlag = false;
            }
            else
                releaseFlag = true;
        }

        if (releaseFlag || m_Parent->GetColliderActiveFlag() == false)
            m_Parent = nullptr;
    }
    else
    {
        m_Velocity += m_Gravity;
    }

    switch (m_UnitState)
    {
    case UNIT_STATE::APPEAR:    Appear();      break;
    case UNIT_STATE::ATTACK:    Attack();      break;
    case UNIT_STATE::DEFEAT:    Defeat();      break;
    }
}

/*
 *  描画
 */
void
IUnit::
Draw(void)
{
}

/*
 *  解放
 */
void
IUnit::
Finalize(void)
{
}

/*
 *  アタリ判定チェック
 */
bool
IUnit::
CheckHitBullet(IBullet* bullet)
{
    if (!bullet || m_Category == bullet->GetBulletCategory() || m_UnitState == UNIT_STATE::DEFEAT)
        return false;
    DxLib::MV1_COLL_RESULT_POLY_DIM hit_poly_dim{};
    switch (bullet->GetColliderID())
    {
    case COLLIDER_ID::SPHERE:
        hit_poly_dim = MV1CollCheck_Sphere(m_Model.GetModelHandle(), -1, bullet->GetPosition(), bullet->GetRadius());
        break;
    case COLLIDER_ID::CAPSULE:
        hit_poly_dim = MV1CollCheck_Capsule(m_Model.GetModelHandle(), -1, bullet->GetColliderPosA(), bullet->GetColliderPosB(),bullet->GetRadius());
        break;
    }
    bool hit_flag = false;

    if (hit_poly_dim.HitNum >= 1)
    {
        hit_flag = true;
        CVector3 hitPosition;
        hitPosition.x = hit_poly_dim.Dim->HitPosition.x;
        hitPosition.y = hit_poly_dim.Dim->HitPosition.y;
        hitPosition.z = hit_poly_dim.Dim->HitPosition.z;

        CEffectManager::GetInstance().Create(EFFECT_ID::HIT, hitPosition);

        bullet->SetActive(false);

        if (m_InvincibleFlag)
            return hit_flag;

        HitBullet(bullet, hitPosition);
    }
    // 当たり判定情報の後始末
    MV1CollResultPolyDimTerminate(hit_poly_dim);
    return hit_flag;
}


bool IUnit::CheckHitBulletModel(IBullet* bullet)
{
    if (!bullet || m_Category == bullet->GetBulletCategory() || m_UnitState == UNIT_STATE::DEFEAT)
        return false;
    DxLib::MV1_COLL_RESULT_POLY_DIM hit_poly_dim{};
    hit_poly_dim = MV1CollCheck_Sphere(bullet->GetModel().GetModelHandle(), -1, GetPosition(), GetRadius());
    bool hit_flag = false;

    if (hit_poly_dim.HitNum >= 1)
    {
        hit_flag = true;
        CVector3 hitPosition;
        hitPosition.x = hit_poly_dim.Dim->HitPosition.x;
        hitPosition.y = hit_poly_dim.Dim->HitPosition.y;
        hitPosition.z = hit_poly_dim.Dim->HitPosition.z;

        CEffectManager::GetInstance().Create(EFFECT_ID::HIT, hitPosition);


        if (m_InvincibleFlag)
            return hit_flag;
        CVector3 direction = bullet->GetVelocity().Normalize();
        if (bullet->GetID() == BULLET_ID::SHOCK_WAVE)
        {
            direction = hit_poly_dim.Dim->Normal;
        }
        Impact(hitPosition, direction, bullet->GetPower());
        bullet->SetActive(false);
    }
    // 当たり判定情報の後始末
    MV1CollResultPolyDimTerminate(hit_poly_dim);
    return hit_flag;
}

/*
 *  ユニットID取得
 */
UNIT_ID
IUnit::
GetUnitID(void)
{
    return m_UnitID;
}

/*
 *  位置取得
 */
CVector3
IUnit::
GetPosition(void)
{
    return m_Transform.position;
}

/*
 *  位置設定
 */
void
IUnit::
SetPosition(const CVector3& positioin)
{
    m_Transform.position = positioin;
}

/*
 *  アクティブフラグ取得
 */
bool
IUnit::
IsActive(void)
{
    return m_ActiveFlag;
}

/*
 *  削除
 */
void
IUnit::
Delete()
{
    m_ActiveFlag = false;
}

/*
 *  ユニット識別子取得
 */
UNIT_CATEGORY
IUnit::
GetUnitCategory(void)
{
    return m_Category;
}

/*
 *  無敵フラグ取得
 */
bool
IUnit::
GetInvincibleFlag(void)
{
    return m_InvincibleFlag;
}

/*
 *  無敵フラグ設定
 */
void
IUnit::
SetInvincibleFlag(bool flag)
{
    m_InvincibleFlag = flag;
}

/*
 *  ユニット状態取得
 */
UNIT_STATE
IUnit::
GetUnitState(void)
{
    return m_UnitState;
}

/*
 *  ユニット状態設定
 */
void
IUnit::
SetUnitState(UNIT_STATE state)
{
    m_UnitState = state;
}

CVector3 IUnit::GetVelocity()
{
    return m_Velocity;
}

void IUnit::SetVelocity(const CVector3& velocity)
{
    m_Velocity = velocity;
}


void IUnit::AddAffectedVelocity(CVector3 velocity)
{
    m_AffectedVelocity += velocity;
}

void IUnit::SetAffectedVelocity(CVector3 velocity)
{
    m_AffectedVelocity = velocity;
}

float IUnit::GetRadius(void)
{
    return m_Radius;
}

float IUnit::GetHeight(void)
{
    return m_Height;
}

void IUnit::SetForwardVector(const CVector3& forward_vector)
{
    if (forward_vector != CVector3::ZERO)
    {
        m_ForwardVector = forward_vector;
    }
}

CVector3 IUnit::GetForwardVector()
{
    return m_ForwardVector;
}

void IUnit::AddShot(void)
{
    m_Shot->AddShot();
}

void IUnit::AddBullet(void)
{
    m_Shot->AddBullet();
}

void IUnit::DamageUp(float damageRate)
{
    m_DamageRate += damageRate;
}

float IUnit::GetDamageRate(void)
{
    return m_DamageRate;
}

bool IUnit::GetDefeatFlag(void)
{
    return m_DefeatFlag;
}

void IUnit::SetDefeatFlag(bool flag)
{
    m_DefeatFlag = flag;
}

CModel IUnit::GetModel(void)
{
    return m_Model;
}

void IUnit::SetIsGround(bool flag)
{
    m_IsGround = flag;
}

bool IUnit::GetIsGround()
{
    return m_IsGround;
}

void IUnit::SetGravity(const CVector3& gravity)
{
    m_Gravity = gravity;
}

CVector3 IUnit::GetDefaultGravity()
{
    return m_gravity;
}

void IUnit::RevertAlpha(float alpha = 1.0f)
{
    //アルファ値が設定値になったら終了
    if (m_Alpha >= alpha)
    {
        m_Alpha = alpha;
        return;
    }

    m_Alpha += m_alpha_speed;

    MV1SetOpacityRate(m_Model.GetModelHandle(), m_Alpha);
}

void IUnit::SetAlpha(float alpha)
{
    m_Alpha = alpha;
    MV1SetOpacityRate(m_Model.GetModelHandle(), m_Alpha);

}

IObject* IUnit::GetParent(void)
{
    return m_Parent;
}

void IUnit::SetParent(IObject* parent)
{
    m_Parent = parent;
}

void IUnit::DecAlpha(float alpha)
{
    //アルファ値が設定値になったら終了
    if (m_Alpha == alpha)
    {
        m_Alpha = alpha;
        return;
    }

    if (m_Alpha > 0.0f)
        m_Alpha -= m_alpha_speed;
    else
        m_Alpha = 0.0f;

    MV1SetOpacityRate(m_Model.GetModelHandle(), m_Alpha);

}

void IUnit::Appear(void)
{
    RevertAlpha();
    if (m_Alpha == 1.0f)
        m_UnitState = UNIT_STATE::ATTACK;

}

/*
 *  攻撃
 */
void
IUnit::
Attack(void)
{
}

void IUnit::Fire(CShot* shot, bool aim, CVector3& position)
{
    IUnit* player = nullptr;
    CVector3 dir = CVector3::BACK;
    if (!shot)
        return;
    if (aim)
    {
        player = CUnitManager::GetInstance().GetPlayer(UNIT_ID::PLAYER1);
    }
    if (player)
    {
        dir = player->GetPosition() - position;

        dir = dir.Normalize();

    }
    shot->Shot(m_Category, position, dir);

}

void IUnit::Fire(CShot* shot, bool aim, CVector3& position, const CVector3& direction)
{
    IUnit* player = nullptr;
    CVector3 dir = direction;
    if (!shot)
        return;
    if (aim)
    {
        player = CUnitManager::GetInstance().GetPlayer(UNIT_ID::PLAYER1);
    }
    if (player)
    {
        dir = player->GetPosition() - position;

        dir = dir.Normalize();

    }
    shot->Shot(m_Category, position, dir);
}

void IUnit::HitBullet(IBullet* bullet, CVector3 hit_position)
{
    //継承先で処理を作る
}

void IUnit::Impact(const CVector3& hit_position, const CVector3& direction, const float power)
{
}

/*
 *  死亡
 */
void
IUnit::
Defeat(void)
{
    m_DefeatFlag = true;
}