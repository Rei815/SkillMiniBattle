#include "boss_enemy.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../unit_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../ui_manager/ui_manager.h"

const float               CBossEnemy::m_max_life = 500;
const float             CBossEnemy::m_move_speed = 5.0f;
const float             CBossEnemy::m_radius = 120.0f;
const float             CBossEnemy::m_attack_time = 600.0f;
const CVector3          CBossEnemy::m_scale = CVector3(2,2,2);
const float             CBossEnemy::m_fall_accelerator = 0.1f;
const int               CBossEnemy::m_wait_time = 60;

CBossEnemy::CBossEnemy()
    : IUnit(m_max_life, UNIT_CATEGORY::ENEMY, UNIT_ID::BOSS_ENEMY)
    , m_Accelerator(CVector3())
    , m_StartPosition(CVector3())
    , m_WaitPosition(CVector3())
    , m_ShockWavePos(CVector3())
    , m_AttackPattern(ATTACK_PATTERN::FALL_ATTACK)
    , m_WaitTimer(0)
    , m_FallSpeed(0)
    , m_BossLife(false)
{
}

CBossEnemy::~CBossEnemy()
{
}

void CBossEnemy::Initialize(const CVector3& position, MOVE_ID moveID, bool aimFlag)
{
    (void)position;

    IUnit::Initialize(position, moveID, aimFlag);

    m_Model.Initialize("data\\Models\\boss.mv1", position);
    // ３Ｄモデルに含まれる０番目のマテリアルのディフューズカラーを真っ赤にします
    MV1SetMaterialDifColor(m_Model.GetModelHandle(), 0, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
    //大きさを変える
    MV1SetScale(m_Model.GetModelHandle(), CVector3(m_scale.x, m_scale.y, m_scale.z));
    m_Life = 1.0f;
    m_MaxLife = m_max_life;
    m_StartPosition = position;
    m_AttackTimer = m_attack_time;
    m_AttackPattern = ATTACK_PATTERN::FALL_ATTACK;
    m_Radius = m_radius;
    m_WaitTimer = m_wait_time;
    m_FallSpeed = 0;
    m_AimFlag = aimFlag;
    CLauncher& lan = CLauncher::GetInstance();

    m_ShotHomingShotgun = lan.Create(SHOT_ID::HOMING_SHOTGUN);

    m_ShotHomingDelayShotgun = lan.Create(SHOT_ID::HOMING_SHOTGUN_DELAY);

    m_ShotShockWave1 = lan.Create(SHOT_ID::SHOCK_WAVE);
    m_ShotShockWave2 = lan.Create(SHOT_ID::SHOCK_WAVE);
    m_ShotShockWave3 = lan.Create(SHOT_ID::SHOCK_WAVE);

    m_ShotShotgun = lan.Create(SHOT_ID::SHOTGUN);
    m_InvincibleFlag = true;
}

void CBossEnemy::Update(void)
{
    
    IUnit::Update();

    m_Model.Update(m_Transform);

    _Attack();
}

void CBossEnemy::Draw(void)
{
    IUnit::Draw();
    m_Model.Draw();
}

void CBossEnemy::Finalize(void)
{
    IUnit::Finalize();
    m_Model.Finalize();

}


/*
 *  攻撃
 */
void
CBossEnemy::
Attack(void)
{

}

void CBossEnemy::_Attack(void)
{
    switch (m_AttackPattern)
    {
    case ATTACK_PATTERN::WAIT:          Wait();     break;
    case ATTACK_PATTERN::MOVE_ATTACK:   MoveAttack();     break;
    case ATTACK_PATTERN::STAY_ATTACK:   StayAttack();     break;
    case ATTACK_PATTERN::FALL_ATTACK:   FallAttack();     break;
    }

}

/*
 *  死亡
 */
void
CBossEnemy::
Dead(void)
{
        m_ActiveFlag = false;
}

/*
 *  登場
 */
void CBossEnemy::Appear(void)
{
    m_Life += 4.0f;
    if (m_Life > m_MaxLife)
        m_Life = m_MaxLife;

    if (!m_DecAlpha && !m_RevertAlpha && m_Transform.position.y <= 100.0f)
    {
        m_InvincibleFlag = false;
        m_UnitState = UNIT_STATE::ATTACK;
    }
}
void CBossEnemy::Wait(void)
{
    if (--m_WaitTimer < 0)
    {
        m_WaitTimer = m_wait_time;
        m_DecAlpha = true;
        m_AttackPattern = ATTACK_PATTERN::MOVE_ATTACK;
    }
}
/*
 *  攻撃パターンA
 */
void CBossEnemy::MoveAttack(void)
{
    Fire(m_ShotHomingDelayShotgun, m_AimFlag, m_Transform.position, CVector3::ZERO);
    Fire(m_ShotShotgun, m_AimFlag, m_Transform.position);
    if (m_MoveId != MOVE_ID::WAIT) Move();

}

/*
 *  攻撃パターンB
 */
void CBossEnemy::StayAttack(void)
{
    if (m_DecAlpha)
        DecAlpha();
    if (m_Alpha == 0.0f)
    {
        m_Transform.position = m_WaitPosition;
        m_RevertAlpha = true;
    }

    if (m_RevertAlpha)
        RevertAlpha();

    if (m_Alpha == 1.0f)
    {
        Fire(m_ShotHomingShotgun, m_AimFlag, m_Transform.position);
        if (--m_AttackTimer < 0)
        {
            m_AttackTimer = m_attack_time;
            m_DecAlpha = true;
            m_AttackPattern = ATTACK_PATTERN::FALL_ATTACK;
        }

    }

}
void CBossEnemy::FallAttack(void)
{
    if (m_DecAlpha)
        DecAlpha();
    if (m_Alpha == 0.0f)
    {
        m_Transform.position = m_StartPosition;
        m_RevertAlpha = true;
    }

    if (m_RevertAlpha)
        RevertAlpha();

    if (m_Alpha == 1.0f)
    {
        m_Velocity.y = -m_FallSpeed;

        m_FallSpeed += m_fall_accelerator;

        m_Transform.position.y += m_Velocity.y;

    }
    if (!m_DecAlpha && !m_RevertAlpha && m_Transform.position.y <= 100.0f)
    {
        m_Transform.position.y = 100.0f;


        m_FallSpeed = 0;

        m_WaitPosition = m_Transform.position;

        m_ShockWavePos = m_Transform.position;
        m_ShockWavePos.y = 0;

        Fire(m_ShotShockWave1, false, m_ShockWavePos);
        Fire(m_ShotShockWave2, false, m_ShockWavePos, CVector3::BACK + CVector3::LEFT);
        Fire(m_ShotShockWave3, false, m_ShockWavePos, CVector3::BACK + CVector3::RIGHT);

        CEffectManager::GetInstance().Create(EFFECT_ID::SHOCK_WAVE, m_ShockWavePos, 2.0f * 24.0f);

        m_Velocity = CVector3::ZERO;
        m_AttackPattern = ATTACK_PATTERN::WAIT;
    }

}

/*
 *  移動
 */
void CBossEnemy::Move(void)
{
    const float MAX_MOVE_X = 1400;

    if (--m_AttackTimer < 0)
    {
        m_AttackTimer = m_attack_time;
        m_AttackPattern = ATTACK_PATTERN::STAY_ATTACK;
    }
    if (m_Transform.position.x < -MAX_MOVE_X + m_radius)
        m_MoveId = MOVE_ID::RIGHT;
    else if (MAX_MOVE_X - m_radius < m_Transform.position.x)
        m_MoveId = MOVE_ID::LEFT;

    m_Velocity.x = ((int)m_MoveId - 1) * m_move_speed;

    m_Transform.position += m_Velocity;

    m_Accelerator = CVector3::ZERO;

}
