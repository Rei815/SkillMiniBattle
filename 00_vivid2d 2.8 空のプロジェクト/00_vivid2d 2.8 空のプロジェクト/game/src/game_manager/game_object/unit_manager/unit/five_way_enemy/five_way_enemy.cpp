#include "five_way_enemy.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../unit_manager.h"


const CVector3          CFiveWayEnemy::m_StartValue = CVector3(0, 0, 0);
const float             CFiveWayEnemy::m_max_life = 2.0f;
const float             CFiveWayEnemy::m_move_speed = 5.0f;
const float             CFiveWayEnemy::m_radius = 50.0f;

CFiveWayEnemy::CFiveWayEnemy()
    : IUnit(m_max_life, UNIT_CATEGORY::ENEMY, UNIT_ID::FIVE_WAY_ENEMY)
    , m_Accelerator(CVector3())

{
}

CFiveWayEnemy::~CFiveWayEnemy()
{
}

void CFiveWayEnemy::Initialize(const CVector3& position, MOVE_ID moveID, bool aimFlag)
{
    (void)position;

    IUnit::Initialize(position, moveID, aimFlag);

    m_Model.Initialize("data\\Models\\cube.mv1", position);
    m_Life = m_MaxLife = m_max_life;
    m_Accelerator = CVector3(0, 0, 0);
    m_Radius = m_radius;
    m_Velocity.x = m_move_speed;
    CLauncher& lan = CLauncher::GetInstance();
    m_Shot = lan.Create(SHOT_ID::FIVE_WAY);

}

void CFiveWayEnemy::Update(void)
{
    IUnit::Update();
    m_Model.Update(m_Transform);

}

void CFiveWayEnemy::Draw(void)
{
    IUnit::Draw();
    m_Model.Draw();
}

void CFiveWayEnemy::Finalize(void)
{
    IUnit::Finalize();
    m_Model.Finalize();

}


/*
 *  çUåÇ
 */
void
CFiveWayEnemy::
Attack(void)
{

    Fire(m_Shot, m_AimFlag, m_Transform.position);
    if (m_MoveId != MOVE_ID::WAIT) Move();
}

/*
 *  à⁄ìÆ
 */
void CFiveWayEnemy::Move(void)
{
    if (m_Transform.position.x < -1400 + m_radius)
        m_Accelerator.x += m_move_speed;
    else if (1400 - m_radius < m_Transform.position.x)
        m_Accelerator.x += -m_move_speed;

    m_Velocity += m_Accelerator;

    m_Transform.position += m_Velocity;

    m_Accelerator = CVector3::ZERO;

}

/*
 *  éÄñS
 */
void
CFiveWayEnemy::
Dead(void)
{
    m_ActiveFlag = false;
}