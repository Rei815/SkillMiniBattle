#include "skill_slow.h"
#include "../../../sound_manager/sound_manager.h"

const float CSkillSlow::m_cool_time = 20.0f;
const float CSkillSlow::m_duration_time = 3.0f;

CSkillSlow::CSkillSlow(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
{
}

CSkillSlow::~CSkillSlow(void)
{
}

void CSkillSlow::Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);

}

void CSkillSlow::Update(void)
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

void CSkillSlow::Draw(void)
{
	CSkill::Draw();
}

void CSkillSlow::Finalize(void)
{
	CSkill::Finalize();
}

void CSkillSlow::Action()
{
	if (m_State != SKILL_STATE::WAIT)	return;

	CSoundManager::GetInstance().Play_SE(SE_ID::SLOW, false);

	for (int i = 0; i < dm.GetCurrentPlayer(); i++)
	{
		if (um.GetPlayer(UNIT_ID(i)) != m_Player)
		{
			um.GetPlayer(UNIT_ID(i))->MulMoveSpeedRate(0.5f);
		}
	}

		m_State = SKILL_STATE::ACTIVE;
}

void CSkillSlow::ActionEnd(void)
{
	for (int i = 0; i < dm.GetCurrentPlayer(); i++)
	{
		if (um.GetPlayer(UNIT_ID(i)) != m_Player)
		{
			um.GetPlayer(UNIT_ID(i))->DivMoveSpeedRate(0.5f);
		}
	}
}