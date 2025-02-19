#include "player.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../unit_manager.h"
#include "../../../ui_manager/ui_manager.h"
#include "../../../object_manager/object_manager.h"


const float             CPlayer::m_radius = 50.0f;
const float             CPlayer::m_height = 70.0f;
const float             CPlayer::m_model_scale = 0.33f;

const float             CPlayer::m_move_speed = 0.6f;
const float             CPlayer::m_jump_power = 20.0f;
const CVector3          CPlayer::m_move_friction = CVector3(0.9f,0.975f,0.9f);
const float             CPlayer::m_fly_away_speed = 40.0f;

const float             CPlayer::m_max_life = 3.0f;
const float             CPlayer::m_max_invincible_time = 1.0f;
const int               CPlayer::m_invincible_visible_interval = 4;
const float             CPlayer::m_fall_accelerator = 0.025f;

const unsigned int      CPlayer::m_player_body_color[] =
{
    0xffffaaaa,     //Player1
    0xffaaaaff,     //Player2
    0xffffffaa,     //Player3
    0xffaaffaa      //Player4
};

const unsigned int      CPlayer::m_player_eye_color[] =
{
    0xff660000,     //Player1
    0xff000066,     //Player2
    0xff666600,     //Player3
    0xff006600      //Player4
};

CPlayer::CPlayer()
    : IUnit(UNIT_CATEGORY::PLAYER)
    , m_MoveSpeedRate(1.0f)
    , m_JumpPowerRate(1.0f)
    , m_Skill(nullptr)
    , m_Accelerator(CVector3::ZERO)
    , m_InvincibleTimer(m_max_invincible_time)
//    , m_FallSpeed(0)
    , m_StopFlag(false)
    , m_FrictionFlag(true)
    , m_ActionFlag(true)
    , m_Controller()
    , m_Effect(nullptr)
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
    case UNIT_ID::PLAYER1: 
        m_Category = UNIT_CATEGORY::PLAYER1;
        break;
    case UNIT_ID::PLAYER2: 
        m_Category = UNIT_CATEGORY::PLAYER2;

        break;
    case UNIT_ID::PLAYER3: 
        m_Category = UNIT_CATEGORY::PLAYER3;

        break;
    case UNIT_ID::PLAYER4: 
        m_Category = UNIT_CATEGORY::PLAYER4;

        break;
    }

    m_Radius = m_radius;
    m_Height = m_height;
    m_Transform.scale = CVector3(m_model_scale, m_model_scale, m_model_scale);

    m_InitialPosition = position;

    m_Model.Initialize(file_name, position, m_model_scale);

    m_Model.SetMaterialDif(0, m_player_body_color[(int)id]);
    m_Model.SetMaterialDif(1, m_player_eye_color[(int)id]);

    m_Accelerator = CVector3(0,0,0);

    m_InvincibleTimer.SetUp(m_max_invincible_time);

    m_StopFlag = false;
    m_FrictionFlag = true;
    m_Controller = controller;
}

void CPlayer::Update(void)
{
    IUnit::Update();
    CVector3 TempForwardVector;

    //�ړ����Ȃ�A���ʕ������ړ������ŃZ�b�g
    if (abs(m_Velocity.x) > 0.0f || abs(m_Velocity.z) > 0.0f)
        TempForwardVector = CVector3(m_Velocity.x, 0, m_Velocity.z).Normalize();
    else
        TempForwardVector = m_ForwardVector;

    //�G���[�`�F�b�N�i�ړ����x�̃x�N�g��������������Ƃ��A�[���x�N�g���Ƃ��Ĕ��肳��Ă��܂��A�G���[�Ƃ��ĕԂ��ꂽ���l�ɂ���Čv�Z���ʂ��ς�邱�Ƃ����邽�߁j
    if (TempForwardVector.x != -1.0f || TempForwardVector.z != -1.0f)
    {
        m_ForwardVector = TempForwardVector;

        //�G���[�łȂ���΁A��]���Z�b�g
        float RotY = CVector3().GetVectorRotateXYZ(m_ForwardVector).y;
        m_Transform.rotation.y = RotY;
    }

    m_Model.Update(m_Transform);
}

void CPlayer::Draw(void)
{
    IUnit::Draw();
    m_Model.Draw();
#if _DEBUG

    vivid::DrawText(30, std::to_string(m_IsGround), vivid::Vector2(1000, 500));
#endif // _DEBUG

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

    //���ړ�
    if (GetJoypadInputState(joyPad) & PAD_INPUT_LEFT || vivid::keyboard::Button(vivid::keyboard::KEY_ID::A))
        Input = true;

    //�E�ړ�
    if (GetJoypadInputState(joyPad) & PAD_INPUT_RIGHT || vivid::keyboard::Button(vivid::keyboard::KEY_ID::D))
        Input = true;

    //��ړ�
    if (GetJoypadInputState(joyPad) & PAD_INPUT_UP || vivid::keyboard::Button(vivid::keyboard::KEY_ID::W))
        Input = true;

    //���ړ�
    if (GetJoypadInputState(joyPad) & PAD_INPUT_DOWN || vivid::keyboard::Button(vivid::keyboard::KEY_ID::S))
        Input = true;


    //�W�����v
    if (m_IsGround && ((GetJoypadInputState(joyPad) & PAD_INPUT_1) || vivid::keyboard::Button(vivid::keyboard::KEY_ID::SPACE)) && !m_StopFlag)
        Input = true;

    //if (m_IsGround == false)
        //Input = true;

    return Input;
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
    if (m_InvincibleFlag)
        return;
    
    m_ActionFlag = false;
    m_FrictionFlag = false;
    m_InvincibleFlag = true;
    m_IsGround = false;
    m_Accelerator = CVector3::ZERO;
    m_Accelerator.y = m_jump_power;

    //�Ռ���^����
    Impact(hit_position, bullet->GetVelocity().Normalize(), bullet->GetPower());
}

/*
*  �Ռ�
*/
void CPlayer::Impact(const CVector3& hit_position, const CVector3& direction, float power)
{
    CVector3 m_EffectPosition = this->GetPosition();

    m_Effect = CEffectManager::GetInstance().Create(EFFECT_ID::COLLIDE, m_EffectPosition, CVector3(), 3.0f);

    //���������������擾
    CVector3 TempVelocity = (m_Transform.position - hit_position);
    //���������̑��x�͍Ō�Ɍv�Z����̂ŁA��x�[���ɂ���
    TempVelocity.y = 0.0f;
    //�x�N�g���̑傫�����Q�ɂ���
    TempVelocity = TempVelocity.Normalize() * 2.0f;
    //�e�̑��x�x�N�g���̑傫�����P�ɂ��ĉ��Z����i�������������ƒe�̑��x���^�t�̏ꍇ�ɁA���������̑��x���ł��������̂�h�����߁j
    TempVelocity += direction;
    //���������̑��x�͍Ō�Ɍv�Z����̂ŁA�Ăу[���ɂ���
    TempVelocity.y = 0.0f;
    //���x��{���Œ������邽�߁A�x�N�g���̑傫�����P�ɂ���
    TempVelocity = TempVelocity.Normalize();
    //���������̃x�N�g����ǉ�
    TempVelocity.y = 0.2f;
    //���g�̈ړ����x���[���ɂ��A�O������̉e���ɂ��ړ����x���x�N�g���Ƃ��̔{���ŃZ�b�g����
    m_Velocity = CVector3::ZERO;
    SetAffectedVelocity(TempVelocity * m_fly_away_speed * power);
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
    {
        m_Accelerator.x += m_move_speed * m_MoveSpeedRate;
    }
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
            m_Parent = nullptr;
            m_IsGround = false;

            m_Accelerator.y = m_jump_power * m_JumpPowerRate;

            CEffectManager::GetInstance().Create(EFFECT_ID::JUMP, m_Transform.position);

        }
    
    //�X�L��
    if(m_Skill != nullptr)
        if ((GetJoypadInputState(joyPad) & PAD_INPUT_2 || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN)) && !m_StopFlag)
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
    {
        m_Velocity += m_Accelerator;
        m_Transform.position += m_Velocity + m_AffectedVelocity;
    }

    IObject* floorObject = CObjectManager::GetInstance().CheckHitObject(this);
    
    if (floorObject)
    {
        if (floorObject->GetTag() == "Floor")
        {
            m_Parent = floorObject;
            m_IsGround = true;
        }
    }
    else if(m_Parent == nullptr)
    {
        m_IsGround = false;
    }

    if (m_FrictionFlag)
    {
        m_Velocity.x *= m_move_friction.x;
        m_Velocity.y *= m_move_friction.y;
        m_Velocity.z *= m_move_friction.z;

        m_AffectedVelocity.x *= m_move_friction.x;
        m_AffectedVelocity.y *= m_move_friction.y;
        m_AffectedVelocity.z *= m_move_friction.z;
    }

    if (m_IsGround)
    {
        if(m_Velocity.y > 0.0f)
            m_Velocity.y = 0.0f;

        if(m_AffectedVelocity.y > 0.0f)
            m_AffectedVelocity.y = 0.0f;

//        m_FallSpeed = 0.0f;
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