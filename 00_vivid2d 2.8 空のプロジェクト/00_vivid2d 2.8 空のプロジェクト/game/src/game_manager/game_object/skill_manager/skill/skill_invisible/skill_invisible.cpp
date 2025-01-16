#include "skill_invisible.h"


const float CSkillInvisible::m_cool_time = 10.0f;
const float CSkillInvisible::m_duration_time = 3.0f;

CSkillInvisible::CSkillInvisible(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
	, m_Active(false)
{
}

CSkillInvisible::~CSkillInvisible(void)
{
}

void CSkillInvisible::Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

void CSkillInvisible::Update(void)
{
	CSkill::Update();

	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		m_Player->SetAlpha(1.0f);
		break;

	case SKILL_STATE::ACTIVE:
		m_Player->DecAlpha(0.5f);
		break;

	case SKILL_STATE::COOLDOWN:
		m_Player->RevertAlpha(1.0f);
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

void CSkillInvisible::Action(void)
{
	if (m_State == SKILL_STATE::WAIT)
	{
		m_Player->StartInvincible(m_duration_time);
		m_State = SKILL_STATE::ACTIVE;
	}
}

/*!
 *  @brief      �A�N�V�����I��
 */
void CSkillInvisible::ActionEnd(void)
{

}