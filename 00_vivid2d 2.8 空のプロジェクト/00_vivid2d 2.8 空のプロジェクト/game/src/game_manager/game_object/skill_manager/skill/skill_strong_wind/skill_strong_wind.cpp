#include "skill_strong_wind.h"
#include "../../../unit_manager/unit_manager.h"

const float CSkillStrongWind::m_wind_strength = 0.1f;
const float CSkillStrongWind::m_cool_time = 5.0f;
const float CSkillStrongWind::m_duration_time = 5.0f;

CSkillStrongWind::CSkillStrongWind(void)
	:CSkill()
{

}

CSkillStrongWind::~CSkillStrongWind(void)
{

}

/*!
 *  @brief      初期化
 */
void
CSkillStrongWind::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
	m_Timer.SetUp(m_duration_time);
}

/*!
 *  @brief      更新
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
		m_Timer.Update();
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
		m_GaugePercent = (m_duration_time - m_Timer.GetTimer()) / m_duration_time * 100.0f;

		if (m_Timer.Finished())
		{
			m_Timer.SetUp(m_cool_time);
			m_State = SKILL_STATE::COOLDOWN;
		}
		break;
	case SKILL_STATE::COOLDOWN:
		m_Timer.Update();

		m_GaugePercent = m_Timer.GetTimer() / m_cool_time * 100.0f;

		if (m_Timer.Finished())
			m_State = SKILL_STATE::WAIT;

		break;
	}

}

/*!
 *  @brief      描画
 */
void
CSkillStrongWind::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CSkillStrongWind::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      アクション呼び出し
 */
void
CSkillStrongWind::
Action(void)
{
	if (m_State != SKILL_STATE::WAIT) return;
	m_Timer.SetUp(m_duration_time);
	m_State = SKILL_STATE::ACTIVE;
}