#include "skill_invisible.h"

const float CSkillInvisible::m_cool_time = 5.0f;
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

void CSkillInvisible::Initialize(CPlayer* player)
{
	CSkill::Initialize(player);
	m_State = STATE::WAIT;

	m_Timer.SetUp(m_invisible_time);
}

void CSkillInvisible::Update(void)
{
	CSkill::Update();
	m_Timer.Update();

	switch (m_State)
	{
	case CSkillInvisible::STATE::WAIT:
		break;

	case CSkillInvisible::STATE::INVISIBLE:

		m_Player->DecAlpha(0.5f);
		if (m_Timer.Finished())
		{
			m_State = CSkillInvisible::STATE::IS_COOL_TIME;
			m_Timer.SetUp(m_cool_time);
			m_Timer.Reset();
		}

		break;

	case CSkillInvisible::STATE::IS_COOL_TIME:


		if (m_Timer.Finished())
		{
			m_State = CSkillInvisible::STATE::WAIT;
		}

		break;
	default:
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
		m_State = CSkillInvisible::STATE::INVISIBLE;
		m_Timer.SetUp(m_invisible_time);
	}
}
