#include "skill_stun.h"
#include "../../../sound_manager/sound_manager.h"

const float CSkillStun::m_cool_time = 20.0f;
const float CSkillStun::m_duration_time = 2.0f;
const float CSkillStun::m_effect_scale = 2.0f;

CSkillStun::CSkillStun(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
	,m_Target(nullptr)
	,m_SkillEffect(nullptr)
	,m_Effect(nullptr)
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

	CSoundManager::GetInstance().Play_SE(SE_ID::STUN, false);
	std::list<std::shared_ptr<CPlayer>>TopPlayerList;

	TopPlayerList.emplace_back(um.GetPlayer(UNIT_ID(0)));

	for (int i = 1; i < dm.GetCurrentJoinPlayer(); i++)
	{
		if (um.GetPlayer(UNIT_ID(i))->GetPosition().x > (*TopPlayerList.begin())->GetPosition().x)
		{
			TopPlayerList.clear();
			TopPlayerList.emplace_back(um.GetPlayer(UNIT_ID(i)));

		}
		else if (um.GetPlayer(UNIT_ID(i))->GetPosition().x == (*TopPlayerList.begin())->GetPosition().x)
		{
			TopPlayerList.emplace_back(um.GetPlayer(UNIT_ID(i)));
		}
	}

	int TargetPlayer = rand() % TopPlayerList.size();
	std::list<std::shared_ptr<CPlayer>>::iterator it = TopPlayerList.begin();
	std::next(it, TargetPlayer);

	m_Target = *it;
	
	if (m_Target == m_Player.lock())
		return;

	m_Target->SetActionFlag(false);

	m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, CVector3().ZERO, CVector3(), m_effect_scale);
	m_Effect = CEffectManager::GetInstance().Create(EFFECT_ID::OGRE_CONTROL, m_Target->GetPosition(), CVector3(), 2.0f);

	m_SkillEffect->SetParent(m_Player.lock());
	m_State = SKILL_STATE::ACTIVE;
}

void CSkillStun::ActionEnd()
{
	if (m_Target != nullptr)
	{
		m_Target->SetActionFlag(true);
		m_Target = nullptr;
	}

	if (m_SkillEffect != nullptr)
	{
		m_SkillEffect->SetActive(false);
		m_SkillEffect = nullptr;
	}

	if (m_Effect != nullptr)
	{
		m_Effect->SetActive(false);
		m_Effect = nullptr;
	}
}