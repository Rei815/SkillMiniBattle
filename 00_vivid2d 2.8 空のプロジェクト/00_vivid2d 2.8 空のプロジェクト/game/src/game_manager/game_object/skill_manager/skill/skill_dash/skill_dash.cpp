#include "skill_dash.h"
#include "../../../unit_manager/unit_manager.h"

const float CSkillDash::m_dash_speed_up_rate = 5.0f;
const float CSkillDash:: m_dash_time = 0.35f;
const float CSkillDash:: m_dash_cool_time = 5.0f;

CSkillDash::CSkillDash(void)
	:CSkill(SKILL_CATEGORY::ACTIVE)
	, m_Timer()
{

}

CSkillDash::~CSkillDash(void)
{

}

/*!
 *  @brief      初期化
 */
void
CSkillDash::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);

	m_State = SKILL_STATE::WAIT;

	m_Timer.SetUp(m_dash_time);
}

/*!
 *  @brief      更新
 */
void
CSkillDash::
Update(void)
{
	CSkill::Update();

	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;

	case SKILL_STATE::ACTIVE:
		m_Timer.Update();
		m_GaugePercent = (m_dash_time - m_Timer.GetTimer()) / m_dash_time * 100.0f;
		if (m_Timer.Finished())
		{
			m_Player->DivMoveSpeedRate(m_dash_speed_up_rate);
			m_Timer.SetUp(m_dash_cool_time);
			m_State = SKILL_STATE::COOLDOWN;
		}
		break;

	case SKILL_STATE::COOLDOWN:
		m_Timer.Update();
		m_GaugePercent = m_Timer.GetTimer() / m_dash_cool_time * 100.0f;
		if (m_Timer.Finished())
		{
			m_Timer.SetUp(m_dash_time);
			m_State = SKILL_STATE::WAIT;
		}
		break;
	}
}

/*!
 *  @brief      描画
 */
void
CSkillDash::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CSkillDash::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      アクション呼び出し
 */
void
CSkillDash::
Action(void)
{
	if (m_State != SKILL_STATE::WAIT)
		return;

	m_Player->MulMoveSpeedRate(m_dash_speed_up_rate);
	m_Timer.SetUp(m_dash_time);
	m_State = SKILL_STATE::ACTIVE;
}