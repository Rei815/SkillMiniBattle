#include "skill_spawn_wall.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../object_manager/object_manager.h"
#include "../../../bullet_manager/bullet_manager.h"

const float CSkillSpawnWall::m_spawn_cool_time = 20.0f;
const float CSkillSpawnWall::m_wall_exist_time = 5.0f;
const float CSkillSpawnWall::m_wall_spawn_distance = 200.0f;

CSkillSpawnWall::CSkillSpawnWall(void)
	:CSkill(SKILL_CATEGORY::ACTIVE)
	, m_NowState(STATE::WAIT)
	, m_Timer()
	, m_WallObj(nullptr)
{

}

CSkillSpawnWall::~CSkillSpawnWall(void)
{

}

/*!
 *  @brief      初期化
 */
void
CSkillSpawnWall::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);

	m_NowState = STATE::WAIT;

	m_Timer.SetUp(m_wall_exist_time);
}

/*!
 *  @brief      更新
 */
void
CSkillSpawnWall::
Update(void)
{
	CSkill::Update();

	switch (m_NowState)
	{
	case CSkillSpawnWall::STATE::WAIT:
		break;

	case CSkillSpawnWall::STATE::SPAWN:
		m_Timer.Update();
		if (m_Timer.Finished())
		{
			m_Timer.SetUp(m_spawn_cool_time);
			m_NowState = STATE::WAIT;

			if (m_WallObj != nullptr)
				m_WallObj->SetActive(false);

			m_WallObj = nullptr;
		}
		else
		{
			if (m_WallObj != nullptr)
				CBulletManager::GetInstance().CheckReflectModel(m_WallObj->GetModel());
		}
		break;

	case CSkillSpawnWall::STATE::IS_COOL_TIME:
		m_Timer.Update();
		if (m_Timer.Finished())
		{
			m_Timer.SetUp(m_wall_exist_time);
			m_NowState = STATE::WAIT;
		}
		break;
	}
}

/*!
 *  @brief      描画
 */
void
CSkillSpawnWall::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CSkillSpawnWall::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      アクション呼び出し
 */
void
CSkillSpawnWall::
Action(void)
{
	if (m_NowState != STATE::WAIT)
		return;

	CTransform SpawnTr;
	
	//スポーンするオブジェクトの座標
	SpawnTr.position = m_Player->GetPosition() + m_Player->GetForwardVector() * m_wall_spawn_distance;

	//スポーンするオブジェクトの向き
	CVector3 TempVector = m_Player->GetForwardVector();
	float TempRotY = asin(TempVector.x) * 180.0f / DX_PI_F;
	if (TempVector.x < 0)
		TempRotY = -TempRotY;
	SpawnTr.rotation = CVector3(0, TempRotY, 0);
	
	m_WallObj = CObjectManager::GetInstance().Create(OBJECT_ID::SKILL_WALL_OBJECT,SpawnTr);
	m_Timer.SetUp(m_wall_exist_time);
	m_NowState = STATE::SPAWN;
}