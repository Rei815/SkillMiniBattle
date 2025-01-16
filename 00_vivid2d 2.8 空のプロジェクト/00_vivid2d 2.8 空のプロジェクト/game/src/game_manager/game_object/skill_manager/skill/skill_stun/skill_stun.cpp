#include "skill_stun.h"


const float CSkillStun::m_cool_time = 20.0f;
const float CSkillStun::m_duration_time = 2.0f;

CSkillStun::CSkillStun(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
{
}

CSkillStun::~CSkillStun(void)
{
}

void CSkillStun::Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

void CSkillStun::Update(void)
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
		m_State = SKILL_STATE::ACTIVE;
	}
}

void CSkillStun::ActionEnd()
{
	for (int i = 0; i < dm.GetCurrentPlayer(); i++)
	{
		um.GetPlayer(UNIT_ID(i))->SetActionFlag(true);
	}
}