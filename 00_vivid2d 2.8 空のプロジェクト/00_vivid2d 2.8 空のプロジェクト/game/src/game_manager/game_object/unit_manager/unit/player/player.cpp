#include "player.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../unit_manager.h"
#include "../../../ui_manager/ui_manager.h"
#include "../../../object_manager/object_manager.h"


const float             CPlayer::m_radius = 50.0f;
const float             CPlayer::m_height = 100.0f;

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
    , m_MoveSpeedRate(1.0f)
    , m_JumpPowerRate(1.0f)
    , m_Skill(nullptr)
    , m_Accelerator(CVector3())
    , m_InvincibleTime(0)
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

    if (m_Velocity != CVector3::ZERO)
        m_ForwardVector = CVector3(m_Velocity.x, 0, m_Velocity.z).Normalize();
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

vivid::controller::DEVICE_ID CPlayer::GetController()
{
    return m_Controller;
}

bool CPlayer::GetPlayerMoving()
{
    return     vivid::controller::GetAnalogStickLeft(m_Controller).x != 0.0f ||
        vivid::controller::GetAnalogStickLeft(m_Controller).y != 0.0f    ;
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
    m_MoveSpeedRate = m_MoveSpeedRate * rate;
}

void CPlayer::DivMoveSpeedRate(float rate)
{
    m_MoveSpeedRate = m_MoveSpeedRate / rate;
}

void CPlayer::SetJumpPowerRate(float rate)
{
    m_JumpPowerRate = rate;
}

void CPlayer::MulJumpPowerRate(float rate)
{
    m_JumpPowerRate = m_JumpPowerRate * rate;
}

void CPlayer::DivJumpPowerRate(float rate)
{
    m_JumpPowerRate = m_JumpPowerRate / rate;
}


/*
 *  �U��
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
 *  ��e
 */
void CPlayer::HitBullet(IBullet* bullet, CVector3 hit_position)
{
    m_ActionFlag = false;
    m_FrictionFlag = false;
    m_InvincibleFlag = true;
    m_IsGround = false;
    m_Accelerator = CVector3::ZERO;
    m_Accelerator.y = m_jump_power;

    //���������������擾
    CVector3 TempVelocity = (m_Transform.position - hit_position);
    //���������̑��x�͍Ō�Ɍv�Z����̂ŁA��x�[���ɂ���
    TempVelocity.y = 0.0f;
    //�x�N�g���̑傫�����Q�ɂ���
    TempVelocity = TempVelocity.Normalize() * 2.0f;
    //�e�̑��x�x�N�g���̑傫�����P�ɂ��ĉ��Z����i�������������ƒe�̑��x���^�t�̏ꍇ�ɁA���������̑��x���ł��������̂�h�����߁j
    TempVelocity += (bullet->GetVelocity().Normalize());
    //���������̑��x�͍Ō�Ɍv�Z����̂ŁA�Ăу[���ɂ���
    TempVelocity.y = 0.0f;
    //���x��{���Œ������邽�߁A�x�N�g���̑傫�����P�ɂ���
    TempVelocity = TempVelocity.Normalize();
    //���������̃x�N�g����ǉ�
    TempVelocity.y = 0.2f;
    //���x���x�N�g���Ƃ��̔{���ŃZ�b�g����
    m_Velocity = TempVelocity * m_fly_away_speed;
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
    //���ړ�
    if (GetJoypadInputState(joyPad) & PAD_INPUT_LEFT || vivid::keyboard::Button(vivid::keyboard::KEY_ID::A))
        m_Accelerator.x += -m_move_speed * m_MoveSpeedRate;

    //�E�ړ�
    if (GetJoypadInputState(joyPad) & PAD_INPUT_RIGHT || vivid::keyboard::Button(vivid::keyboard::KEY_ID::D))
        m_Accelerator.x += m_move_speed * m_MoveSpeedRate;
    //��ړ�
    if (GetJoypadInputState(joyPad) & PAD_INPUT_UP || vivid::keyboard::Button(vivid::keyboard::KEY_ID::W))
        m_Accelerator.z += m_move_speed * m_MoveSpeedRate;

    //���ړ�
    if (GetJoypadInputState(joyPad) & PAD_INPUT_DOWN || vivid::keyboard::Button(vivid::keyboard::KEY_ID::S))
        m_Accelerator.z += -m_move_speed * m_MoveSpeedRate;


    //�W�����v
    if (m_IsGround && ((GetJoypadInputState(joyPad) & PAD_INPUT_1) || vivid::keyboard::Button(vivid::keyboard::KEY_ID::SPACE)) && !m_StopFlag)
        if (m_IsGround == true)
        {
            m_IsGround = false;

            m_Accelerator.y = m_jump_power * m_JumpPowerRate;

            CEffectManager::GetInstance().Create(EFFECT_ID::JUMP, m_Transform.position);

        }

    //�X�L��
    if(m_Skill != nullptr)
        if (((GetJoypadInputState(joyPad) & PAD_INPUT_1) || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN)) && !m_StopFlag)
            m_Skill->Action();

    //��~
    if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::LSHIFT))
        m_StopFlag = true;
    else
        m_StopFlag = false;

}

/*
 *  ���S
 */
void
CPlayer::
Defeat(void)
{
    IUnit::Defeat();

}

void CPlayer::Move(void)
{
    ////�d�͏���
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
    if (floorObject)
    {
        if (floorObject->GetTag() == "Floor")
            m_IsGround = true;
    }
    else
        m_IsGround = false;

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