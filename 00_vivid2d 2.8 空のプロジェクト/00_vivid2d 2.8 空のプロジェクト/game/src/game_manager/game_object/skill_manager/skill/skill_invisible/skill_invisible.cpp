#include "skill_invisible.h"


const float CSkillInvisible::m_cool_time = 2.0f;
const float CSkillInvisible::m_active_time = 2.0f;

CSkillInvisible::CSkillInvisible(void)
	:CSkill(SKILL_CATEGORY::ACTIVE)
	, m_Timer()
{
}

CSkillInvisible::~CSkillInvisible(void)
{
}

void CSkillInvisible::Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
	m_State = SKILL_STATE::WAIT;
	m_Timer.SetUp(m_active_time);
}

void CSkillInvisible::Update(void)
{
	CSkill::Update();
	m_Timer.Update();

	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;
	case SKILL_STATE::ACTIVE:
		m_Player->DecAlpha(0.5f);
		if (m_Timer.Finished())
		{
			m_Timer.Reset();
			m_Timer.SetUp(m_cool_time);
			m_State = SKILL_STATE::COOLDOWN;
		}
		break;
	case SKILL_STATE::COOLDOWN:
		m_Player->RevertAlpha(1.0f);

		if (m_Timer.Finished())
		{
			m_Player->SetAlpha(1.0f);
			m_State = SKILL_STATE::WAIT;
		}
		break;
	}
}

void CSkillInvisible::Draw(void)
{
	CSkill::Draw();
}

void CSkillInvisible::Finalize(void)
{
	CSkill::Finalize();
}

void CSkillInvisible::Action()
{
	if (m_State == SKILL_STATE::WAIT)
	{
		m_Player->StartInvincible(m_active_time);
		m_Timer.SetUp(m_active_time);
		m_State = SKILL_STATE::ACTIVE;
	}
}
