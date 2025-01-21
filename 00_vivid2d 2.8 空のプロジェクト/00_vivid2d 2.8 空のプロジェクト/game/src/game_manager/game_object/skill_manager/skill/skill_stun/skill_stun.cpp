#include "skill_stun.h"


const float CSkillStun::m_cool_time = 20.0f;
const float CSkillStun::m_duration_time = 2.0f;

CSkillStun::CSkillStun(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
	,m_Target(nullptr)
{
}

CSkillStun::~CSkillStun(void)
{
}

void CSkillStun::Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
	m_Target = nullptr;
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
	if (m_State != SKILL_STATE::WAIT)
		return;

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
	std::next(it, TargetPlayer);

	m_Target = (*it);
	
	if (m_Target == m_Player)
		return;

	m_Target->SetActionFlag(false);

	m_State = SKILL_STATE::ACTIVE;
}

void CSkillStun::ActionEnd()
{
	if (m_Target != nullptr)
	{
		m_Target->SetActionFlag(true);
		m_Target = nullptr;
	}
}