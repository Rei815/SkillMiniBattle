#include "skill_stomp.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../../effect_manager/effect_manager.h"

const float CSkillStomp::m_cool_time = 5.0f;

CSkillStomp::CSkillStomp(void)
	:CSkill(SKILL_CATEGORY::ACTIVE)
{

}

CSkillStomp::~CSkillStomp(void)
{

}

/*!
 *  @brief      初期化
 */
void
CSkillStomp::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
	m_Category = SKILL_CATEGORY::ACTIVE;
	m_State = SKILL_STATE::WAIT;
}

/*!
 *  @brief      更新
 */
void
CSkillStomp::
Update(void)
{
	CSkill::Update();
	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;
	case SKILL_STATE::ACTIVE:
		break;
	case SKILL_STATE::COOLDOWN:
		m_GaugePercent = m_Timer.GetTimer() / m_cool_time * 100.0f;

		m_Timer.Update();
		if (m_Timer.Finished())
		{
			m_State = SKILL_STATE::WAIT;
			m_Timer.Reset();
		}
		break;
	}
}

/*!
 *  @brief      描画
 */
void
CSkillStomp::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CSkillStomp::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      アクション呼び出し
 */
void
CSkillStomp::
Action()
{
	if (m_State == SKILL_STATE::COOLDOWN) return;
	CBulletManager::GetInstance().Create(m_Player->GetUnitCategory(), BULLET_ID::SHOCK_WAVE, m_Player->GetPosition(), CVector3::UP);
	CEffectManager::GetInstance().Create(EFFECT_ID::SHOCK_WAVE, m_Player->GetPosition());
	m_Timer.SetUp(m_cool_time);
	m_State = SKILL_STATE::COOLDOWN;
}