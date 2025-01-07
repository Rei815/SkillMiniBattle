#include "skill_ogre_control.h"

const float CSkillOgreControl::m_cool_time = 0.0f;
const float CSkillOgreControl::m_active_time = 10.0f;

CSkillOgreControl::CSkillOgreControl(void)
	:CSkill(SKILL_CATEGORY::ACTIVE)
	, m_Timer()
{
}


CSkillOgreControl::~CSkillOgreControl(void)
{
}

void CSkillOgreControl::Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
	m_State = SKILL_STATE::WAIT;
	m_Timer.SetUp(m_active_time);
	m_Target = nullptr;
}

void CSkillOgreControl::Update(void)
{
	CSkill::Update();
	m_Timer.Update();

	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;
	case SKILL_STATE::ACTIVE:

		if (!m_Player->GetPlayerMoving())
		{
			dg.OgreControlTurn();
		}

		if (m_Timer.Finished())
		{
			m_Timer.Reset();
			m_Timer.SetUp(m_cool_time);
			m_State = SKILL_STATE::COOLDOWN;
		}
		break;
	case SKILL_STATE::COOLDOWN:

		if (m_Timer.Finished())
		{
			m_State = SKILL_STATE::WAIT;
		}
		break;
	}
}

void CSkillOgreControl::Draw(void)
{
	CSkill::Draw();
}

void CSkillOgreControl::Finalize(void)
{
	CSkill::Finalize();
}

void CSkillOgreControl::Action()
{
	if (m_State == SKILL_STATE::WAIT)
	{
		m_Timer.SetUp(m_active_time);
		m_State = SKILL_STATE::ACTIVE;
	}
}