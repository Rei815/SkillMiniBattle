#include "skill_strong_wind.h"
#include "../../../unit_manager/unit_manager.h"

const float CSkillStrongWind::m_wind_strength = 0.1f;
const float CSkillStrongWind::m_cool_time = 5.0f;
const float CSkillStrongWind::m_duration_time = 5.0f;

CSkillStrongWind::CSkillStrongWind(void)
	:CSkill(SKILL_CATEGORY::ACTIVE ,m_duration_time, m_cool_time)
{

}

CSkillStrongWind::~CSkillStrongWind(void)
{

}

/*!
 *  @brief      ������
 */
void
CSkillStrongWind::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

/*!
 *  @brief      �X�V
 */
void
CSkillStrongWind::
Update(void)
{
	CSkill::Update();
	CUnitManager::UNIT_LIST unitList = CUnitManager::GetInstance().GetUnitList();
	CUnitManager::UNIT_LIST::iterator it = unitList.begin();
	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;

	case SKILL_STATE::ACTIVE:
		while (it != unitList.end())
		{
			IUnit* unit = (*it);

			if (unit->GetUnitID() != m_Player->GetUnitID())
			{
				CVector3 velocity = unit->GetVelocity();
				velocity.z -= m_wind_strength;
				unit->SetVelocity(velocity);
			}
			++it;
		}
		break;

	case SKILL_STATE::COOLDOWN:
		break;
	}

}

/*!
 *  @brief      �`��
 */
void
CSkillStrongWind::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      ���
 */
void
CSkillStrongWind::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      �A�N�V�����Ăяo��
 */
void
CSkillStrongWind::
Action(void)
{
	if (m_State != SKILL_STATE::WAIT) return;

	m_State = SKILL_STATE::ACTIVE;
}

/*!
 *  @brief      �A�N�V�����I��
 */
void
CSkillStrongWind::
ActionEnd(void)
{

}