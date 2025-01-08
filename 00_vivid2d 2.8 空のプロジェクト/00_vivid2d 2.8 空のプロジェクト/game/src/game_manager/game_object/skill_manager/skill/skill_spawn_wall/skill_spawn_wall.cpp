#include "skill_spawn_wall.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../object_manager/object_manager.h"
#include "../../../bullet_manager/bullet_manager.h"

const float CSkillSpawnWall::m_spawn_cool_time = 15.0f;
const float CSkillSpawnWall::m_wall_exist_time = 5.0f;
const float CSkillSpawnWall::m_wall_spawn_distance = 200.0f;

CSkillSpawnWall::CSkillSpawnWall(void)
	:CSkill(SKILL_CATEGORY::ACTIVE)
	, m_Timer()
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

	m_State = SKILL_STATE::WAIT;

	m_Timer.SetUp(m_wall_exist_time);
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
		m_Timer.Update();

		m_GaugePercent = (m_wall_exist_time - m_Timer.GetTimer()) / m_wall_exist_time * 100.0f;

		if (m_Timer.Finished())
		{
			m_Timer.SetUp(m_spawn_cool_time);
			m_State = SKILL_STATE::COOLDOWN;

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

	case SKILL_STATE::COOLDOWN:
		m_Timer.Update();

		m_GaugePercent = m_Timer.GetTimer() / m_spawn_cool_time * 100.0f;

		if (m_Timer.Finished())
		{
			m_Timer.SetUp(m_wall_exist_time);
			m_State = SKILL_STATE::WAIT;
		}
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
	m_Timer.SetUp(m_wall_exist_time);
	m_State = SKILL_STATE::ACTIVE;
}