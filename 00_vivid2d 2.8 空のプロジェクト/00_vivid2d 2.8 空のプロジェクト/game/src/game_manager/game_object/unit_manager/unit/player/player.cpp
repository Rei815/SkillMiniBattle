#include "player.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../unit_manager.h"
#include "../../../ui_manager/ui_manager.h"
#include "../../../object_manager/object_manager.h"
#include "../../../controller_manager/controller_manager.h"

const std::string       CPlayer::m_file_name = "data\\Models\\player_rabbit.mv1";
const float             CPlayer::m_radius = 50.0f;
const float             CPlayer::m_height = 70.0f;
const float             CPlayer::m_model_scale = 0.33f;
const float             CPlayer::m_move_speed = 0.6f;
const float             CPlayer::m_jump_power = 20.0f;
const float             CPlayer::m_fly_away_speed = 40.0f;
const float             CPlayer::m_max_life = 3.0f;
const float             CPlayer::m_max_invincible_time = 1.0f;
const float             CPlayer::m_fall_accelerator = 0.025f;
const CVector3          CPlayer::m_move_friction = CVector3(0.9f,0.975f,0.9f);
const int               CPlayer::m_invincible_visible_interval = 4;

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
    , m_StopFlag(false)
    , m_FrictionFlag(true)
    , m_ActionFlag(true)
    , m_Controller(nullptr)
{
}

CPlayer::~CPlayer()
{

}

void CPlayer::Initialize(UNIT_ID id, const CVector3& position)
{
    IUnit::Initialize(id, position);
    CControllerManager& cm = CControllerManager::GetInstance();
    CControllerManager::CONTROLLER_LIST controllerList = cm.GetList();
    CControllerManager::CONTROLLER_LIST::iterator it = controllerList.begin();

    //IDによってカテゴリーの切り替え
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
    //コントローラーに設定されているUnitIDと合っている場合自身のコントローラーとして取得
    while (it != controllerList.end())
    {
        if ((*it)->GetUnitID() == id)
        {
            m_Controller = std::shared_ptr<CController>(*it);
            break;
        }
        ++it;
    }
    m_Radius = m_radius;
    m_Height = m_height;
    m_Transform.scale = CVector3(m_model_scale, m_model_scale, m_model_scale);

    m_InitialPosition = position;

    
    
    m_Model.Initialize(m_file_name, position, m_model_scale);

    m_Model.SetMaterialDif(0, m_player_body_color[(int)id]);
    m_Model.SetMaterialDif(1, m_player_eye_color[(int)id]);

    m_Accelerator = CVector3(0,0,0);

    m_InvincibleTimer.SetUp(m_max_invincible_time);

    m_StopFlag = false;
    m_FrictionFlag = true;
}

void CPlayer::Update(void)
{
    IUnit::Update();
    CVector3 TempForwardVector;

    //移動中なら、正面方向を移動方向でセット
    if (abs(m_Velocity.x) > 0.0f || abs(m_Velocity.z) > 0.0f)
        TempForwardVector = CVector3(m_Velocity.x, 0, m_Velocity.z).Normalize();
    else
        TempForwardVector = m_ForwardVector;

    //エラーチェック（移動速度のベクトルが小さすぎるとき、ゼロベクトルとして判定されてしまい、エラーとして返された数値によって計算結果が変わることがあるため）
    if (TempForwardVector.x != -1.0f || TempForwardVector.z != -1.0f)
    {
        m_ForwardVector = TempForwardVector;

        //エラーでなければ、回転をセット
        float RotY = CVector3().GetVectorRotateXYZ(m_ForwardVector).y;
        m_Transform.rotation.y = RotY;
    }

    m_Model.Update(m_Transform);
}

void CPlayer::Draw(void)
{
    IUnit::Draw();
    m_Model.Draw();
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

std::shared_ptr<CSkill> CPlayer::GetSkill()
{
    return m_Skill;
}

bool CPlayer::GetPlayerMoving()
{
    bool Input = false;

    if (m_Controller)
    {
        vivid::Vector2 stick = m_Controller->GetLeftStick();

        //左移動
        if ((stick != vivid::Vector2::ZERO && stick.x < -0.5f))
            Input = true;

        //右移動
        if ((stick != vivid::Vector2::ZERO && stick.x > 0.5f))
            Input = true; 

        //上移動
        if ((stick != vivid::Vector2::ZERO && stick.y < -0.5f))
            Input = true;

        //下移動
        if ((stick != vivid::Vector2::ZERO && stick.y > 0.5f))
            Input = true;

        //ジャンプ
        if (m_Controller->GetButtonDown(BUTTON_ID::A) && !m_StopFlag)
            Input = true;

    }


    return Input;
}

void CPlayer::SetSkill(std::shared_ptr<CSkill> skill)
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
void CPlayer::HitBullet(std::shared_ptr<IBullet> bullet, CVector3 hit_position)
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
    //自身の移動速度をゼロにし、外部からの影響による移動速度をベクトルとその倍率でセットする
    m_Velocity = CVector3::ZERO;
    SetAffectedVelocity(TempVelocity * m_fly_away_speed * power);
}
void CPlayer::Control(void)
{
    if (m_Controller == nullptr) return;
    vivid::Vector2 stick = m_Controller->GetLeftStick();
    //左移動
    if ((stick != vivid::Vector2::ZERO && stick.x < -0.5f))
        m_Accelerator.x += -m_move_speed * m_MoveSpeedRate;

    //右移動
    if ((stick != vivid::Vector2::ZERO && stick.x > 0.5f))
        m_Accelerator.x += m_move_speed * m_MoveSpeedRate;
    //上移動
    if ((stick != vivid::Vector2::ZERO && stick.y < -0.5f))
        m_Accelerator.z += m_move_speed * m_MoveSpeedRate;

    //下移動
    if ((stick != vivid::Vector2::ZERO && stick.y > 0.5f))
        m_Accelerator.z += -m_move_speed * m_MoveSpeedRate;


    //ジャンプ
    if (m_Controller->GetButtonDown(BUTTON_ID::A) && !m_StopFlag)
        if (m_IsGround == true)
        {
            m_Parent = nullptr;
            m_IsGround = false;

            m_Accelerator.y = m_jump_power * m_JumpPowerRate;

            CEffectManager::GetInstance().Create(EFFECT_ID::JUMP, m_Transform.position);

        }
    
    //スキル
    if(m_Skill != nullptr)
        if (m_Controller->GetButtonDown(BUTTON_ID::B) && !m_StopFlag)
            m_Skill->Action();

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
    if (m_Parent != nullptr)
    {
        //一度接地したらジャンプや判定の外に行かない限り接地したオブジェクトに追従する
        const float ground_check_offset_x = m_Radius - m_Radius / 3.0f;
        const float ground_check_line_length = 100.0f;
        bool releaseFlag = false;
        for (int i = 0; i < 9; i++)
        {
            CVector3 start = m_Transform.position + CVector3(-ground_check_offset_x + (ground_check_offset_x) * (i % 3), 0.0f, -ground_check_offset_x + (ground_check_offset_x) * (i / 3));
            CVector3 end = start + CVector3(0, -ground_check_line_length, 0);
            CVector3 hitPos = m_Parent->GetModel().GetHitLinePosition(start, end);
            if (hitPos != end)
            {
                m_Transform.position.y = hitPos.y + m_Radius;
            }
            else
            {
                releaseFlag = true;
                break;
            }
        }

        if (releaseFlag || m_Parent->GetColliderActiveFlag() == false)
            m_Parent = nullptr;
    }
    else
    {
        m_Velocity += m_Gravity;
    }

    if (!m_StopFlag)
    {
        m_Velocity += m_Accelerator;
        m_Transform.position += m_Velocity + m_AffectedVelocity;
    }

    std::shared_ptr<IObject> floorObject = CObjectManager::GetInstance().CheckHitObject(shared_from_this());
    
    //床に当たっているならそのオブジェクトを親にする
    if (floorObject)
    {
        if (floorObject->GetTag() == "Floor")
        {
            m_Parent = floorObject;
            m_IsGround = true;
            m_Velocity.y = 0;
        }
    }
    else if(m_Parent == nullptr)
    {
        m_IsGround = false;
    }

    //摩擦による減速
    if (m_FrictionFlag)
    {
        m_Velocity.x *= m_move_friction.x;
        m_Velocity.y *= m_move_friction.y;
        m_Velocity.z *= m_move_friction.z;

        m_AffectedVelocity.x *= m_move_friction.x;
        m_AffectedVelocity.y *= m_move_friction.y;
        m_AffectedVelocity.z *= m_move_friction.z;
    }

    //地上なら落ちないように
    if (m_IsGround)
    {
        if(m_Velocity.y > 0.0f)
            m_Velocity.y = 0.0f;

        if(m_AffectedVelocity.y > 0.0f)
            m_AffectedVelocity.y = 0.0f;
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