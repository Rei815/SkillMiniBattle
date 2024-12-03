#include "skill_dash.h"
#include "../../../unit_manager/unit_manager.h"

const float CSkillDash::m_dash_speed_up_rate = 5.0f;
const float CSkillDash:: m_dash_time = 0.35f;
const float CSkillDash:: m_dash_cool_time = 5.0f;

CSkillDash::CSkillDash(void)
	:CSkill()
	, m_NowDashState(DASH_STATE::WAIT)
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
Initialize(CPlayer* player)
{
	CSkill::Initialize(player);

	m_NowDashState = DASH_STATE::WAIT;

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

	switch (m_NowDashState)
	{
	case CSkillDash::DASH_STATE::WAIT:
		break;

	case CSkillDash::DASH_STATE::IS_DASH:
		m_Timer.Update();
		if (m_Timer.Finished())
		{
			m_Player->DivMoveSpeedRate(m_dash_speed_up_rate);
			m_Timer.SetUp(m_dash_cool_time);
			m_NowDashState = DASH_STATE::IS_COOL_TIME;
		}
		break;

	case CSkillDash::DASH_STATE::IS_COOL_TIME:
		m_Timer.Update();
		if (m_Timer.Finished())
		{
			m_Timer.SetUp(m_dash_time);
			m_NowDashState = DASH_STATE::WAIT;
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
	if (m_NowDashState != DASH_STATE::WAIT)
		return;

	m_Player->MulMoveSpeedRate(m_dash_speed_up_rate);
	m_Timer.SetUp(m_dash_time);
	m_NowDashState = DASH_STATE::IS_DASH;
}