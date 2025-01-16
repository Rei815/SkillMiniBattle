#include "skill_resurrect_daruma.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../data_manager/data_manager.h"

const float CSkillResurrectDaruma::m_duration_time = 2.0f;

CSkillResurrectDaruma::CSkillResurrectDaruma(void)
	:CSkill(SKILL_CATEGORY::PASSIVE, m_duration_time)
{
}

CSkillResurrectDaruma::~CSkillResurrectDaruma(void)
{
}

void CSkillResurrectDaruma ::Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

void CSkillResurrectDaruma::Update(void)
{
	CSkill::Update();
	
	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;
	case SKILL_STATE::ACTIVE:
		break;
	case SKILL_STATE::COOLDOWN:
		break;
	}
}

void CSkillResurrectDaruma::Draw(void)
{
	CSkill::Draw();
}

void CSkillResurrectDaruma::Finalize(void)
{
	CSkill::Finalize();
}

void CSkillResurrectDaruma::Action(void)
{
}

void CSkillResurrectDaruma::ActionEnd(void)
{
	m_Player->SetActionFlag(true);
}
