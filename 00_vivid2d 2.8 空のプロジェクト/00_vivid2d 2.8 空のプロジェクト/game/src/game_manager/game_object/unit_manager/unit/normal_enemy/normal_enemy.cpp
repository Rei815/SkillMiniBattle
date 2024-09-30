#include "normal_enemy.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../unit_manager.h"


const CVector3          CNormalEnemy::m_StartValue = CVector3(0,0,0);
const float             CNormalEnemy::m_max_life = 2.0f;
const float             CNormalEnemy::m_move_speed = 5.0f;
const float             CNormalEnemy::m_radius = 50.0f;

CNormalEnemy::CNormalEnemy()
    : IUnit(m_max_life, UNIT_CATEGORY::ENEMY, UNIT_ID::NORMAL_ENEMY)
    , m_Accelerator(CVector3())

{
}

CNormalEnemy::~CNormalEnemy()
{
}

void CNormalEnemy::Initialize(const CVector3& position, MOVE_ID moveID, bool aimFlag)
{
    (void)position;

    IUnit::Initialize(position, moveID, aimFlag);

    m_Model.Initialize("data\\Models\\cube.mv1", position);
    m_Life = m_MaxLife = m_max_life;
    m_Accelerator = CVector3(0, 0, 0);
    m_Radius = m_radius;
    m_Velocity.x = m_move_speed;
    CLauncher& lan = CLauncher::GetInstance();
    m_Shot = lan.Create(SHOT_ID::BASIC);

}

void CNormalEnemy::Update(void)
{
    IUnit::Update();
    m_Model.Update(m_Transform);

}

void CNormalEnemy::Draw(void)
{
    IUnit::Draw();
    m_Model.Draw();
}

void CNormalEnemy::Finalize(void)
{
    IUnit::Finalize();
    m_Model.Finalize();

}


/*
 *  çUåÇ
 */
void
CNormalEnemy::
Attack(void)
{

    Fire(m_Shot, m_AimFlag, m_Transform.position);
    if (m_MoveId != MOVE_ID::WAIT) Move();
}

/*
 *  à⁄ìÆ
 */
void CNormalEnemy::Move(void)
{
    if (m_Transform.position.x < -1400 + m_radius)
        m_Accelerator.x += m_move_speed;
    else if(1400 - m_radius < m_Transform.position.x)
        m_Accelerator.x += -m_move_speed;

    m_Velocity += m_Accelerator;

    m_Transform.position += m_Velocity;

    m_Accelerator = CVector3::ZERO;

}

/*
 *  éÄñS
 */
void
CNormalEnemy::
Dead(void)
{
    m_ActiveFlag = false;
}