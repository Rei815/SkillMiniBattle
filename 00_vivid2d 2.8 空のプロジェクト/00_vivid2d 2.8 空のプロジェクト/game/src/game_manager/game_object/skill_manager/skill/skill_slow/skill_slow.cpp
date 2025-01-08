#include "skill_slow.h"

const float CSkillSlow::m_cool_time = 10.0f;
const float CSkillSlow::m_active_time = 3.0f;

CSkillSlow::CSkillSlow(void)
	:CSkill(SKILL_CATEGORY::ACTIVE)
	, m_Timer()
{
}

CSkillSlow::~CSkillSlow(void)
{
}

void CSkillSlow::Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
	m_State = SKILL_STATE::WAIT;
	m_Timer.SetUp(m_active_time);
	m_Target = nullptr;
}

void CSkillSlow::Update(void)
{
	CSkill::Update();
	m_Timer.Update();

	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;
	case SKILL_STATE::ACTIVE:
		m_GaugePercent = (m_active_time - m_Timer.GetTimer()) / m_active_time * 100.0f;

		if (m_Timer.Finished())
		{
			m_Target->DivMoveSpeedRate(0.5f);

			m_Timer.Reset();
			m_Timer.SetUp(m_cool_time);
			m_State = SKILL_STATE::COOLDOWN;
		}
		break;
	case SKILL_STATE::COOLDOWN:
		m_GaugePercent = m_Timer.GetTimer() / m_cool_time * 100.0f;

		if (m_Timer.Finished())
		{
			m_State = SKILL_STATE::WAIT;
		}
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
	if (m_State == SKILL_STATE::WAIT)
	{
		std::list<CPlayer*>TopPlayerList;

		TopPlayerList.push_back(um.GetPlayer(UNIT_ID(0)));

		for (int i = 1; i < dm.GetCurrentPlayer(); i++)
		{
			if (um.GetPlayer(UNIT_ID(i))->GetPosition().x > (*TopPlayerList.begin())->GetPosition().x)
			{
				TopPlayerList.clear();
				TopPlayerList.push_back(um.GetPlayer(UNIT_ID(i)));

			}
			else if (um.GetPlayer(UNIT_ID(i))->GetPosition().x == (*TopPlayerList.begin())->GetPosition().x)
			{
				TopPlayerList.push_back(um.GetPlayer(UNIT_ID(i)));
			}
		}

		int TargetPlayer = rand() % TopPlayerList.size();
		std::list<CPlayer*>::iterator it = TopPlayerList.begin();

		std::next(it,TargetPlayer);

		m_Target = (*it);
		m_Target->MulMoveSpeedRate(0.5f);

		m_Timer.SetUp(m_active_time);
		m_State = SKILL_STATE::ACTIVE;
	}
}