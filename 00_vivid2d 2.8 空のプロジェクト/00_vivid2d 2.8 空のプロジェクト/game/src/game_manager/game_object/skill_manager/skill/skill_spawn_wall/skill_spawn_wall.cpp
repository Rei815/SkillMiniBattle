#include "skill_spawn_wall.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../object_manager/object_manager.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../../sound_manager/sound_manager.h"

const float CSkillSpawnWall::m_cool_time = 15.0f;
const float CSkillSpawnWall::m_duration_time = 5.0f;
const float CSkillSpawnWall::m_wall_spawn_distance = 200.0f;

CSkillSpawnWall::CSkillSpawnWall(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
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
}

/*!
 *  @brief      更新
 */
void
CSkillSpawnWall::
Update(void)
{
	CSkill::Update();

	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;

	case SKILL_STATE::ACTIVE:
		if (m_WallObj != nullptr)
			CBulletManager::GetInstance().CheckReflectModel(m_WallObj->GetModel());
		break;

	case SKILL_STATE::COOLDOWN:
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
	if (m_State != SKILL_STATE::WAIT)
		return;

	CSoundManager::GetInstance().Play_SE(SE_ID::SPAWN_WALL, false);

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
	m_State = SKILL_STATE::ACTIVE;
}

/*!
 *  @brief      アクション終了
 */
void
CSkillSpawnWall::
ActionEnd(void)
{
	if (m_WallObj != nullptr)
	{
		m_WallObj->SetActive(false);
		m_WallObj = nullptr;
	}
}