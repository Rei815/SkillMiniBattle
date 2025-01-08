#include "skill_stun.h"


const float CSkillStun::m_cool_time = 20.0f;
const float CSkillStun::m_active_time = 3.0f;




CSkillStun::CSkillStun(void)
	:CSkill(SKILL_CATEGORY::ACTIVE)
	, m_Timer()
{
}

CSkillStun::~CSkillStun(void)
{
}

void CSkillStun::Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
	m_State = SKILL_STATE::WAIT;
	m_Timer.SetUp(m_active_time);
}

void CSkillStun::Update(void)
{
	CSkill::Update();
	m_Timer.Update();

	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;
	case SKILL_STATE::ACTIVE:

		if (m_Timer.Finished())
		{
			

			for (int i = 0; i < dm.GetCurrentPlayer(); i++)
			{
					um.GetPlayer(UNIT_ID(i))->SetActionFlag(true);
			}
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

void CSkillStun::Draw(void)
{
	CSkill::Draw();
}

void CSkillStun::Finalize(void)
{
	CSkill::Finalize();
}

void CSkillStun::Action()
{
	if (m_State == SKILL_STATE::WAIT)
	{
		for (int i = 0; i < dm.GetCurrentPlayer();i++)
		{
			if (um.GetPlayer(UNIT_ID(i)) != m_Player)
			{
				um.GetPlayer(UNIT_ID(i))->SetActionFlag(false);
			}
		}
		m_Timer.SetUp(m_active_time);
		m_State = SKILL_STATE::ACTIVE;
	}
}