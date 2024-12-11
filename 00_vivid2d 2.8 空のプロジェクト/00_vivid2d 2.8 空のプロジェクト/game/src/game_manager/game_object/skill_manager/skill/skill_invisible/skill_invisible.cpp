#include "skill_invisible.h"

const float CSkillInvisible::m_cool_time = 2.0f;
const float CSkillInvisible::m_invisible_time = 5.0f;

CSkillInvisible::CSkillInvisible(void)
	:CSkill(SKILL_CATEGORY::ACTIVE)
	, m_State(STATE::WAIT)
	, m_Timer()
{
}

CSkillInvisible::~CSkillInvisible(void)
{
}

void CSkillInvisible::Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
	m_State = STATE::WAIT;
	m_Timer.SetUp(m_invisible_time);
}

void CSkillInvisible::Update(void)
{
	CSkill::Update();
	m_Timer.Update();

	switch (m_State)
	{
	case STATE::WAIT:
		break;

	case STATE::INVISIBLE:

		m_Player->DecAlpha(0.5f);
		if (m_Timer.Finished())
		{
			m_Timer.Reset();
			m_Timer.SetUp(m_cool_time);
			m_State = STATE::IS_COOL_TIME;
		}
		break;

	case STATE::IS_COOL_TIME:

		m_Player->RevertAlpha(1.0f);

		if (m_Timer.Finished())
		{
			m_Player->SetAlpha(1.0f);
			m_State = STATE::WAIT;
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
	if (m_State == STATE::WAIT)
	{
		m_Timer.SetUp(m_invisible_time);
		m_State = STATE::INVISIBLE;
	}
}
