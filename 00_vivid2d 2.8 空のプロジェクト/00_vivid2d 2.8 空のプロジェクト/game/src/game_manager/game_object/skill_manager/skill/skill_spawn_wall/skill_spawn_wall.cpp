#include "skill_spawn_wall.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../object_manager/object_manager.h"
#include "../../../bullet_manager/bullet_manager.h"

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
 *  @brief      ������
 */
void
CSkillSpawnWall::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

/*!
 *  @brief      �X�V
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
 *  @brief      �`��
 */
void
CSkillSpawnWall::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      ���
 */
void
CSkillSpawnWall::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      �A�N�V�����Ăяo��
 */
void
CSkillSpawnWall::
Action(void)
{
	if (m_State != SKILL_STATE::WAIT)
		return;

	CTransform SpawnTr;
	
	//�X�|�[������I�u�W�F�N�g�̍��W
	SpawnTr.position = m_Player->GetPosition() + m_Player->GetForwardVector() * m_wall_spawn_distance;

	//�X�|�[������I�u�W�F�N�g�̌���
	CVector3 TempVector = m_Player->GetForwardVector();
	float TempRotY = asin(TempVector.x) * 180.0f / DX_PI_F;
	if (TempVector.x < 0)
		TempRotY = -TempRotY;
	SpawnTr.rotation = CVector3(0, TempRotY, 0);
	
	m_WallObj = CObjectManager::GetInstance().Create(OBJECT_ID::SKILL_WALL_OBJECT,SpawnTr);
	m_State = SKILL_STATE::ACTIVE;
}

/*!
 *  @brief      �A�N�V�����I��
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