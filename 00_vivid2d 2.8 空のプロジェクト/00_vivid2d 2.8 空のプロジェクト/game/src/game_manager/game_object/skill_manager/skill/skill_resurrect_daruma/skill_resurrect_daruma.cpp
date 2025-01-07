#include "skill_resurrect_daruma.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../data_manager/data_manager.h"

const float CSkillResurrectDaruma::m_active_time = 2.0f;

CSkillResurrectDaruma::CSkillResurrectDaruma(void)
	:CSkill(SKILL_CATEGORY::RESURRECT)
	, m_Timer()
{
}

CSkillResurrectDaruma::~CSkillResurrectDaruma(void)
{
}

void CSkillResurrectDaruma ::Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
	m_State = SKILL_STATE::WAIT;
	m_Timer.SetUp(m_active_time);
}

void CSkillResurrectDaruma::Update(void)
{
	CSkill::Update();
	
	if (m_State == SKILL_STATE::ACTIVE)
	{
		m_Timer.Update();

		if (m_Timer.Finished())
		{
			m_State = SKILL_STATE::COOLDOWN;
			m_Player->SetActionFlag(true);
		}
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

void CSkillResurrectDaruma::Action()
{
	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		m_State = SKILL_STATE::ACTIVE;
		break;
	case SKILL_STATE::ACTIVE:
		break;
	case SKILL_STATE::COOLDOWN:
		m_Player->SetPosition(CVector3(-1500, 100, 100));
		break;
	}
}
