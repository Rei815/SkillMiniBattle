#include "player.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../unit_manager.h"
#include "../../../ui_manager/ui_manager.h"


const float             CPlayer::m_radius = 50.0f;
const float             CPlayer::m_height = 10.0f;

const float             CPlayer::m_move_speed = 0.25f;
const float             CPlayer::m_jump_power = 30.0f;
const float             CPlayer::m_move_friction = 0.975f;
const float             CPlayer::m_fly_away_speed = 40.0f;
const float             CPlayer::m_max_life = 3.0f;
const int               CPlayer::m_max_invincible_time = 60;
const int               CPlayer::m_invincible_visible_interval = 4;
const float             CPlayer::m_fall_accelerator = 0.025f;

CPlayer::CPlayer()
    : IUnit(UNIT_CATEGORY::PLAYER)
    , m_Accelerator(CVector3())
    , m_InvincibleTime(0)
    , m_FallSpeed(0)
    , m_StopFlag(false)
    , m_FrictionFlag(true)
    , m_ActionFlag(true)
    , m_Controller()
    , m_WinsNum()
    , m_Color({1,1,1,1})
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initialize(UNIT_ID id, const CVector3& position, const std::string& file_name, int controller)
{
    (void)position;

    IUnit::Initialize(id, position, file_name, controller);

    m_Radius = m_radius;
    m_Height = m_height;

    m_InitialPosition = position;

    m_Model.Initialize(file_name, position);

    MV1SetMaterialDifColor(m_Model.GetModelHandle(), 0, m_Color);

    m_Accelerator = CVector3(0,0,0);

    m_InvincibleTime = m_max_invincible_time;

    m_StopFlag = false;
    m_FrictionFlag = true;
    m_Controller = controller;
}

void CPlayer::Update(void)
{
    IUnit::Update();
    m_Model.Update(m_Transform);
}

void CPlayer::Draw(void)
{
    if ((m_InvincibleTime / m_invincible_visible_interval) % 2 == 1)
    {
        IUnit::Draw();
        m_Model.Draw();
    }
}

void CPlayer::Finalize(void)
{
    IUnit::Finalize();
    m_Model.Finalize();
}

void CPlayer::SetActionFlag(bool flag)
{
    m_ActionFlag = flag;
}

void CPlayer::AddWins()
{
    if (m_WinsNum < 5)
        m_WinsNum++;
}

int CPlayer::GetWins()
{
    return m_WinsNum;
}

int CPlayer::GetController()
{
    return m_Controller;
}

/*
 *  攻撃
 */
void
CPlayer::
Attack(void)
{
    if (m_ActionFlag || !m_DefeatFlag)
    {
        Control();
    }
        Move();

        Damage();
}


/*
 *  被弾
 */
void CPlayer::HitBullet(IBullet* bullet, CVector3 hit_position)
{
    m_ActionFlag = false;
    m_FrictionFlag = false;
    m_InvincibleFlag = true;
    m_Accelerator = CVector3::ZERO;

    //当たった向きを取得
    CVector3 TempVelocity = (m_Transform.position - hit_position);
    //垂直方向の速度は最後に計算するので、一度ゼロにする
    TempVelocity.y = 0.0f;
    //ベクトルの大きさを２にする
    TempVelocity = TempVelocity.Normalize() * 2.0f;
    //弾の速度ベクトルの大きさを１にして加算する（当たった向きと弾の速度が真逆の場合に、横方向の速度が打ち消されるのを防ぐため）
    TempVelocity += (bullet->GetVelocity().Normalize());
    //垂直方向の速度は最後に計算するので、再びゼロにする
    TempVelocity.y = 0.0f;
    //速度を倍率で調整するため、ベクトルの大きさを１にする
    TempVelocity = TempVelocity.Normalize();
    //垂直方向のベクトルを追加
    TempVelocity.y = 1.0f;
    //速度をベクトルとその倍率でセットする
    m_Velocity = TempVelocity * m_fly_away_speed;
}

void CPlayer::Control(void)
{
    //左移動
    if (GetJoypadInputState(m_Controller) & PAD_INPUT_LEFT || vivid::keyboard::Button(vivid::keyboard::KEY_ID::A))
        m_Accelerator.x += -m_move_speed;

    //右移動
    if (GetJoypadInputState(m_Controller) & PAD_INPUT_RIGHT || vivid::keyboard::Button(vivid::keyboard::KEY_ID::D))
        m_Accelerator.x += m_move_speed;
    //上移動
    if (GetJoypadInputState(m_Controller) & PAD_INPUT_UP || vivid::keyboard::Button(vivid::keyboard::KEY_ID::W))
        m_Accelerator.z += m_move_speed;

    //下移動
    if (GetJoypadInputState(m_Controller) & PAD_INPUT_DOWN || vivid::keyboard::Button(vivid::keyboard::KEY_ID::S))
        m_Accelerator.z += -m_move_speed;


    //ジャンプ
    if (m_IsGround && (GetJoypadInputState(m_Controller) & PAD_INPUT_1) || vivid::keyboard::Button(vivid::keyboard::KEY_ID::SPACE) && !m_StopFlag)
        if (m_IsGround == true)
        {
            m_IsGround = false;

            m_Accelerator.y = m_jump_power;

            CEffectManager::GetInstance().Create(EFFECT_ID::JUMP, m_Transform.position);

        }

    //停止
    if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::LSHIFT))
         m_StopFlag = true;
    else m_StopFlag = false;

}

/*
 *  死亡
 */
void
CPlayer::
Defeat(void)
{
    IUnit::Defeat();

}

void CPlayer::Move(void)
{
    ////重力処理
    //if (!m_IsGround && !m_StopFlag)
    //{
    //    m_Accelerator.y -= m_FallSpeed;

    //    m_FallSpeed += m_fall_accelerator;
    //}

    if (!m_StopFlag)
        m_Velocity += m_Accelerator;

    if (!m_StopFlag)
        m_Transform.position += m_Velocity;

    if (m_FrictionFlag)
    {
        m_Velocity.x *= m_move_friction;
        m_Velocity.y *= m_move_friction;
        m_Velocity.z *= m_move_friction;
    }

    if (m_IsGround)
    {
        m_Velocity.y = 0.0f;
        m_Accelerator.y = 0;
        m_FallSpeed = 0.0f;
    }

    m_Accelerator = CVector3::ZERO;
}

void CPlayer::Damage(void)
{
    if (!m_InvincibleFlag)
        return;
    if (--m_InvincibleTime < 0)
    {
        m_InvincibleTime = m_max_invincible_time;

        m_InvincibleFlag = false;
    }

}