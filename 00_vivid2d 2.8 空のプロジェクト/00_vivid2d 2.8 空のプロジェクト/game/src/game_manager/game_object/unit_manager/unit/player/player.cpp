#include "player.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../unit_manager.h"
#include "../../../ui_manager/ui_manager.h"
#include "../../../object_manager/object_manager.h"


const float             CPlayer::m_radius = 50.0f;
const float             CPlayer::m_height = 100.0f;

const float             CPlayer::m_move_speed = 0.25f;
const float             CPlayer::m_jump_power = 20.0f;
const float             CPlayer::m_move_friction = 0.975f;
const float             CPlayer::m_fly_away_speed = 40.0f;

const float             CPlayer::m_max_life = 3.0f;
const float             CPlayer::m_max_invincible_time = 1.0f;
const int               CPlayer::m_invincible_visible_interval = 4;
const float             CPlayer::m_fall_accelerator = 0.025f;

CPlayer::CPlayer()
    : IUnit(UNIT_CATEGORY::PLAYER)
    , m_MoveSpeedRate(1.0f)
    , m_JumpPowerRate(1.0f)
    , m_Skill(nullptr)
    , m_Accelerator(CVector3::ZERO)
    , m_InvincibleTimer(m_max_invincible_time)
    , m_FallSpeed(0)
    , m_StopFlag(false)
    , m_FrictionFlag(true)
    , m_ActionFlag(true)
    , m_Controller()
    , m_Color({1,1,1,1})
    , m_ForwardVector(CVector3::FORWARD)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initialize(UNIT_ID id, const CVector3& position, const std::string& file_name, vivid::controller::DEVICE_ID controller)
{
    (void)position;

    IUnit::Initialize(id, position, file_name, controller);
    switch (id)
    {
    case UNIT_ID::PLAYER1: m_Category = UNIT_CATEGORY::PLAYER1;
        break;
    case UNIT_ID::PLAYER2: m_Category = UNIT_CATEGORY::PLAYER2;
        break;
    case UNIT_ID::PLAYER3: m_Category = UNIT_CATEGORY::PLAYER3;
        break;
    case UNIT_ID::PLAYER4: m_Category = UNIT_CATEGORY::PLAYER4;
        break;
    }
    m_Radius = m_radius;
    m_Height = m_height;

    m_InitialPosition = position;

    m_Model.Initialize(file_name, position);

    MV1SetMaterialDifColor(m_Model.GetModelHandle(), 0, m_Color);

    m_Accelerator = CVector3(0,0,0);

    m_InvincibleTimer.SetUp(m_max_invincible_time);

    m_StopFlag = false;
    m_FrictionFlag = true;
    m_Controller = controller;
}

void CPlayer::Update(void)
{
    IUnit::Update();
    m_Model.Update(m_Transform);

    if (m_Velocity != CVector3::ZERO)
        m_ForwardVector = CVector3(m_Velocity.x, 0, m_Velocity.z).Normalize();
}

void CPlayer::Draw(void)
{
    //if (((int)(m_InvincibleTimer.GetTimer() * 60) / m_invincible_visible_interval) % 2 == 1)
    //{
        IUnit::Draw();
        m_Model.Draw();
    //}
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

vivid::controller::DEVICE_ID CPlayer::GetController()
{
    return m_Controller;
}

CSkill* CPlayer::GetSkill()
{
    return m_Skill;
}

bool CPlayer::GetPlayerMoving()
{
    bool Input = false;

    int     joyPad = 0;
    switch (m_Controller)
    {
    case vivid::controller::DEVICE_ID::PLAYER1: joyPad = DX_INPUT_PAD1; break;
    case vivid::controller::DEVICE_ID::PLAYER2: joyPad = DX_INPUT_PAD2; break;
    case vivid::controller::DEVICE_ID::PLAYER3: joyPad = DX_INPUT_PAD3; break;
    case vivid::controller::DEVICE_ID::PLAYER4: joyPad = DX_INPUT_PAD4; break;
    }

    //左移動
    if (GetJoypadInputState(joyPad) & PAD_INPUT_LEFT || vivid::keyboard::Button(vivid::keyboard::KEY_ID::A))
        Input = true;

    //右移動
    if (GetJoypadInputState(joyPad) & PAD_INPUT_RIGHT || vivid::keyboard::Button(vivid::keyboard::KEY_ID::D))
        Input = true;

    //上移動
    if (GetJoypadInputState(joyPad) & PAD_INPUT_UP || vivid::keyboard::Button(vivid::keyboard::KEY_ID::W))
        Input = true;

    //下移動
    if (GetJoypadInputState(joyPad) & PAD_INPUT_DOWN || vivid::keyboard::Button(vivid::keyboard::KEY_ID::S))
        Input = true;


    //ジャンプ
    if (m_IsGround && ((GetJoypadInputState(joyPad) & PAD_INPUT_1) || vivid::keyboard::Button(vivid::keyboard::KEY_ID::SPACE)) && !m_StopFlag)
        Input = true;

    if (m_IsGround == false)
        Input = true;

    return Input;
}

CVector3 CPlayer::GetForwardVector()
{
    return m_ForwardVector;
}

void CPlayer::SetSkill(CSkill* skill)
{
    m_Skill = skill;
}

void CPlayer::SetMoveSpeedRate(float rate)
{
    m_MoveSpeedRate = rate;
}

void CPlayer::MulMoveSpeedRate(float rate)
{
    if (rate == 0.0f)
        return;

    m_MoveSpeedRate = m_MoveSpeedRate * rate;
}

void CPlayer::DivMoveSpeedRate(float rate)
{
    if (rate == 0.0f)
        return;

    m_MoveSpeedRate = m_MoveSpeedRate / rate;
}

void CPlayer::SetJumpPowerRate(float rate)
{
    m_JumpPowerRate = rate;
}

void CPlayer::MulJumpPowerRate(float rate)
{
    if (rate == 0.0f)
        return;

    m_JumpPowerRate = m_JumpPowerRate * rate;
}

void CPlayer::DivJumpPowerRate(float rate)
{
    if (rate == 0.0f)
        return;

    m_JumpPowerRate = m_JumpPowerRate / rate;
}

void CPlayer::StartInvincible(float invincible_time)
{
    m_InvincibleFlag = true;
    m_InvincibleTimer.SetUp(invincible_time);
}


/*
 *  攻撃
 */
void
CPlayer::
Attack(void)
{
    if (m_ActionFlag && !m_DefeatFlag)
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
    if (m_InvincibleFlag)
        return;
    
    m_ActionFlag = false;
    m_FrictionFlag = false;
    m_InvincibleFlag = true;
    m_IsGround = false;
    m_Accelerator = CVector3::ZERO;
    m_Accelerator.y = m_jump_power;

    //衝撃を与える
    Impact(hit_position, bullet->GetVelocity().Normalize(), bullet->GetPower());
}

/*
*  衝撃
*/
void CPlayer::Impact(const CVector3& hit_position, const CVector3& direction, float power)
{
    //当たった向きを取得
    CVector3 TempVelocity = (m_Transform.position - hit_position);
    //垂直方向の速度は最後に計算するので、一度ゼロにする
    TempVelocity.y = 0.0f;
    //ベクトルの大きさを２にする
    TempVelocity = TempVelocity.Normalize() * 2.0f;
    //弾の速度ベクトルの大きさを１にして加算する（当たった向きと弾の速度が真逆の場合に、水平方向の速度が打ち消されるのを防ぐため）
    TempVelocity += direction;
    //垂直方向の速度は最後に計算するので、再びゼロにする
    TempVelocity.y = 0.0f;
    //速度を倍率で調整するため、ベクトルの大きさを１にする
    TempVelocity = TempVelocity.Normalize();
    //垂直方向のベクトルを追加
    TempVelocity.y = 0.2f;
    //速度をベクトルとその倍率でセットする
    m_Velocity = TempVelocity * m_fly_away_speed * power;

}
void CPlayer::Control(void)
{
    int     joyPad = 0;
    switch (m_Controller)
    {
    case vivid::controller::DEVICE_ID::PLAYER1: joyPad = DX_INPUT_PAD1; break;
    case vivid::controller::DEVICE_ID::PLAYER2: joyPad = DX_INPUT_PAD2; break;
    case vivid::controller::DEVICE_ID::PLAYER3: joyPad = DX_INPUT_PAD3; break;
    case vivid::controller::DEVICE_ID::PLAYER4: joyPad = DX_INPUT_PAD4; break;
    }
    //左移動
    if (GetJoypadInputState(joyPad) & PAD_INPUT_LEFT || vivid::keyboard::Button(vivid::keyboard::KEY_ID::A))
        m_Accelerator.x += -m_move_speed * m_MoveSpeedRate;

    //右移動
    if (GetJoypadInputState(joyPad) & PAD_INPUT_RIGHT || vivid::keyboard::Button(vivid::keyboard::KEY_ID::D))
    {
        m_Accelerator.x += m_move_speed * m_MoveSpeedRate;
    }
    //上移動
    if (GetJoypadInputState(joyPad) & PAD_INPUT_UP || vivid::keyboard::Button(vivid::keyboard::KEY_ID::W))
        m_Accelerator.z += m_move_speed * m_MoveSpeedRate;

    //下移動
    if (GetJoypadInputState(joyPad) & PAD_INPUT_DOWN || vivid::keyboard::Button(vivid::keyboard::KEY_ID::S))
        m_Accelerator.z += -m_move_speed * m_MoveSpeedRate;


    //ジャンプ
    if (m_IsGround && ((GetJoypadInputState(joyPad) & PAD_INPUT_1) || vivid::keyboard::Button(vivid::keyboard::KEY_ID::SPACE)) && !m_StopFlag)
        if (m_IsGround == true)
        {
            m_IsGround = false;

            m_Accelerator.y = m_jump_power * m_JumpPowerRate;

            CEffectManager::GetInstance().Create(EFFECT_ID::JUMP, m_Transform.position);

        }
    
    //スキル
    if(m_Skill != nullptr)
        if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN) && !m_StopFlag)
            m_Skill->Action();

    //停止
    if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::LSHIFT))
        m_StopFlag = true;
    else
        m_StopFlag = false;

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

    IObject* floorObject = CObjectManager::GetInstance().CheckHitObject(this);
    if (!floorObject)
        m_IsGround = false;
    else
        if (floorObject->GetTag() == "Floor")
            m_IsGround = true;

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

    m_InvincibleTimer.Update();
    if (m_InvincibleTimer.Finished())
    {
        m_InvincibleTimer.SetUp(m_max_invincible_time);

        m_InvincibleFlag = false;
    }
}