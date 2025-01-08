#include "skill_strong_wind.h"
#include "../../../unit_manager/unit_manager.h"

const float CSkillStrongWind::m_wind_strength = 1.5f;

CSkillStrongWind::CSkillStrongWind(void)
	:CSkill()
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
				CVector3 velocity = m_Player->GetVelocity();
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
	m_State = SKILL_STATE::ACTIVE;
}