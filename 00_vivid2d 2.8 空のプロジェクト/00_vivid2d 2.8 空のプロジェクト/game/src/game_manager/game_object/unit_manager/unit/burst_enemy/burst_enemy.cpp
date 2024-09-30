#include "burst_enemy.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../unit_manager.h"


const CVector3          CBurstEnemy::m_StartValue = CVector3(0, 0, 0);
const float             CBurstEnemy::m_max_life = 3.0f;
const float             CBurstEnemy::m_move_speed = 5.0f;
const float             CBurstEnemy::m_radius = 50.0f;

CBurstEnemy::CBurstEnemy()
    : IUnit(m_max_life, UNIT_CATEGORY::ENEMY, UNIT_ID::BURST_ENEMY)
    , m_Accelerator(CVector3())

{
}

CBurstEnemy::~CBurstEnemy()
{
}
void CBurstEnemy::Initialize(const CVector3& position, MOVE_ID moveID, bool aimFlag)
{
    (void)position;

    IUnit::Initialize(position, moveID, aimFlag);

    m_Model.Initialize("data\\Models\\cube.mv1", position);
    // ３Ｄモデルに含まれる０番目のマテリアルのディフューズカラーを真っ赤にします
    MV1SetMaterialDifColor(m_Model.GetModelHandle(), 0, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
    m_Life = m_MaxLife = m_max_life;
    m_Velocity.x = m_move_speed;
    m_Radius = m_radius;
    CLauncher& lan = CLauncher::GetInstance();
    m_Shot = lan.Create(SHOT_ID::BURST);

}

void CBurstEnemy::Update(void)
{
    IUnit::Update();
    m_Model.Update(m_Transform);

}

void CBurstEnemy::Draw(void)
{
    IUnit::Draw();
    m_Model.Draw();
}

void CBurstEnemy::Finalize(void)
{
    IUnit::Finalize();
    m_Model.Finalize();

}


/*
 *  攻撃
 */
void
CBurstEnemy::
Attack(void)
{
    Fire(m_Shot, m_AimFlag, m_Transform.position);
    if (m_MoveId != MOVE_ID::WAIT) Move();

}

/*
 *  死亡
 */
void
CBurstEnemy::
Dead(void)
{
    m_ActiveFlag = false;
}

/*
 *  移動
 */
void CBurstEnemy::Move(void)
{
    if (m_Transform.position.x < -1400 + m_radius)
        m_Accelerator.x += m_move_speed;
    else if (1400 - m_radius < m_Transform.position.x)
        m_Accelerator.x += -m_move_speed;

    m_Velocity += m_Accelerator;

    m_Transform.position += m_Velocity;

    m_Accelerator = CVector3::ZERO;

}
