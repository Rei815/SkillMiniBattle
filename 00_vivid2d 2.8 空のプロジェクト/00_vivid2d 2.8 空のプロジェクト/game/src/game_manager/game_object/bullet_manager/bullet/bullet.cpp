
#include "bullet.h"
#include "..\..\..\..\utility\utility.h"
#include "../../launcher/launcher.h"
#include "../../unit_manager/unit_manager.h"

const unsigned int  IBullet::m_player_color = 0xff008fff;
const unsigned int  IBullet::m_enemy_color = 0xffff008f;
const int           IBullet::m_life_time = 240;
const float         IBullet::m_radius = 50.0f;
/*
 *  コンストラクタ
 */
IBullet::
IBullet(const std::string& file_name, COLLIDER_ID collider_id)
    : m_FileName(file_name)
    , m_Category(UNIT_CATEGORY::UNKNOWN)
    , m_Transform(CTransform())
    , m_Velocity(CVector3(CVector3::ZERO))
    , m_Radius(0)
    , m_Color(0xffffffff)
    , m_Rotation(0.0f)
    , m_ActiveFlag(true)
    , m_LifeTimer(0)
    , m_Damage(0.0f)
    , m_ColliderID(collider_id)
    , m_CapsulePosA(CVector3())
    , m_CapsulePosB(CVector3())
    , m_Power(1.0f)
{
}

/*
 *  デストラクタ
 */
IBullet::
~IBullet(void)
{
}

/*
 *  初期化
 */
void
IBullet::
Initialize(UNIT_CATEGORY category, CShot::BulletParameters* bulletParameter, const CVector3& position, const CVector3& direction)
{
    m_Category = category;
    m_Transform.position = position;
    m_Velocity = direction * bulletParameter->speed;
    m_Radius = bulletParameter->radius;
    m_Color = (category == UNIT_CATEGORY::PLAYER ? m_player_color : m_enemy_color);
    m_Model.Initialize(m_FileName, m_Transform.position);
    m_ActiveFlag = true;
    m_Damage = bulletParameter->damage;
    m_LifeTimer = m_life_time;
}

void IBullet::Initialize(UNIT_CATEGORY category, const CVector3& position, const CVector3& direction)
{
    m_Category = category;
    m_Transform.position = position;
    m_Velocity = direction;
    m_Color = (category == UNIT_CATEGORY::PLAYER ? m_player_color : m_enemy_color);
    m_Model.Initialize(m_FileName, m_Transform.position);
    m_ActiveFlag = true;
    m_LifeTimer = m_life_time;

}

/*
 *  更新
 */
void
IBullet::
Update(void)
{

    // 移動計算
    m_Transform.position += m_Velocity;
    m_Model.SetPosition(m_Transform.position);
    m_Model.Update(m_Transform);

    if (--m_LifeTimer < 0)
    {
        m_LifeTimer = m_life_time;

        m_ActiveFlag = false;
    }
}

/*
 *  描画
 */
void
IBullet::
Draw(void)
{
#ifdef VIVID_DEBUG
    // 球の描画
    //int ok = DxLib::DrawSphere3D(m_Transform.position, 50.0f, 8, GetColor(255, 255, 0), GetColor(255, 255, 255), FALSE);
#endif

    m_Model.Draw();
}

/*
 *  解放
 */
void
IBullet::
Finalize(void)
{
    m_Model.Finalize();
}

/*
 *  位置取得
 */
CVector3
IBullet::
GetPosition(void)
{
    return m_Transform.position;
}

/*
 *  位置設定
 */
void
IBullet::
SetPosition(const CVector3& positioin)
{
    m_Transform.position = positioin;
}
/*
 *  速度ベクトル取得
 */
CVector3
IBullet::
GetVelocity(void)
{
    return m_Velocity;
}

/*
 *  半径取得
 */
float
IBullet::
GetRadius(void)
{
    return m_Radius;
}

/*
 *  アクティブフラグ取得
 */
bool
IBullet::
GetActive(void)
{
    return m_ActiveFlag;
}

/*
 *  アクティブフラグ取得
 */
void
IBullet::
SetActive(bool active)
{
    m_ActiveFlag = active;
}

/*
 *  ユニット識別子取得
 */
UNIT_CATEGORY
IBullet::
GetBulletCategory(void)
{
    return m_Category;
}

/*
 *  弾の色取得
 */
unsigned int
IBullet::
GetBulletColor(void)
{
    return m_Color;
}

float
IBullet::
GetBulletDamage(void)
{
    return m_Damage;
}

COLLIDER_ID
IBullet::
GetColliderID(void)
{
    return m_ColliderID;
}

CVector3
IBullet::
GetColliderPosA(void)
{
    return m_Transform.position + m_CapsulePosA;
}

CVector3
IBullet::
GetColliderPosB(void)
{
    return m_Transform.position + m_CapsulePosB;
}

CModel IBullet::GetModel(void)
{
    return m_Model;
}

float IBullet::GetPower()
{
    return m_Power;
}
