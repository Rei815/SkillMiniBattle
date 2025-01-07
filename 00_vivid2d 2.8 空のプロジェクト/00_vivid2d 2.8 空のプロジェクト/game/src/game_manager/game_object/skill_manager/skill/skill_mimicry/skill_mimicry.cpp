#include "skill_mimicry.h"

const float CSkillMimicry::m_cool_time = 2.0f;
const float CSkillMimicry::m_active_time = 5.0f;
CSkillMimicry::CSkillMimicry(void)
	:CSkill(SKILL_CATEGORY::ACTIVE)
	, m_State(SKILL_STATE::WAIT)
	, m_Timer()
{
}

CSkillMimicry::~CSkillMimicry(void)
{
}

void CSkillMimicry::Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
	m_State = SKILL_STATE::WAIT;
	m_Timer.SetUp(m_active_time);
}

void CSkillMimicry::Update(void)
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
			m_Player->DivMoveSpeedRate(0.5f);
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

void CSkillMimicry::Draw(void)
{
	CSkill::Draw();
}

void CSkillMimicry::Finalize(void)
{
	CSkill::Finalize();
}

void CSkillMimicry::Action()
{
	if (m_State == SKILL_STATE::WAIT)
	{
		m_Player->MulMoveSpeedRate(0.5f);
		m_Player->StartInvincible(m_active_time);
		m_Timer.SetUp(m_active_time);
		m_State = SKILL_STATE::ACTIVE;
	}
}
