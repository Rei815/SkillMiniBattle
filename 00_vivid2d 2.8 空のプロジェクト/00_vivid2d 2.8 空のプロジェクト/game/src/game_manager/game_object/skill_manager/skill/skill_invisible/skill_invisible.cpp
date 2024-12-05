#include "skill_invisible.h"

CSkillInvisible::CSkillInvisible(void)
	:CSkill()
	,m_State(STATE::WAIT)
	,m_Timer()
{
}

CSkillInvisible::~CSkillInvisible(void)
{
}

void CSkillInvisible::Initialize(CPlayer* player)
{
	CSkill::Initialize(player);
	m_State = STATE::WAIT;
	m_Timer.SetUp(m_invisibletime);
}

void CSkillInvisible::Update(void)
{
	CSkill::Update();

	switch (m_State)
	{
	case CSkillInvisible::STATE::WAIT:
		break;
	case CSkillInvisible::STATE::INVISIBLE:
		m_Timer.Update();


		break;
	case CSkillInvisible::STATE::IS_COOL_TIME:
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
