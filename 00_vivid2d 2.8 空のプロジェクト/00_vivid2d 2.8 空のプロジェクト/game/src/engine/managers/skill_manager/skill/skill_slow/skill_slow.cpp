#include "skill_slow.h"
#include "../../../sound_manager/sound_manager.h"

const float CSkillSlow::m_cool_time = 20.0f;
const float CSkillSlow::m_duration_time = 3.0f;
const float CSkillSlow::m_effect_scale = 2.0f;

CSkillSlow::CSkillSlow(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
	,m_SkillEffect(nullptr)
	,m_DebuffEffect(nullptr)
	, m_EffectList()
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

	

	for (int i = 0; i < dm.GetCurrentJoinPlayer(); i++)
	{
		if (um.GetPlayer(UNIT_ID(i)) != m_Player.lock())
		{
			um.GetPlayer(UNIT_ID(i))->MulMoveSpeedRate(0.5f);
			m_EffectList.push_front(CEffectManager::GetInstance().Create(EFFECT_ID::DEBUFF, CVector3().ZERO, CVector3(), m_effect_scale));
			m_EffectList.front()->SetParent(um.GetPlayer(UNIT_ID(i)));
		}
	}

	m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, CVector3().ZERO, CVector3(), m_effect_scale);
	m_SkillEffect->SetParent(m_Player.lock());
	m_State = SKILL_STATE::ACTIVE;
}

void CSkillSlow::ActionEnd(void)
{
	if (m_SkillEffect != nullptr)
	{
		m_SkillEffect->Delete(false);
		m_SkillEffect = nullptr;
	}

	if (m_EffectList.empty() == false)
	{
		std::list<std::shared_ptr<IEffect>>::iterator it = m_EffectList.begin();
		while (it != m_EffectList.end())
		{
			(*it)->Delete(false);

			it++;
		}
		m_EffectList.clear();
	}

	for (int i = 0; i < dm.GetCurrentJoinPlayer(); i++)
	{
		if (um.GetPlayer(UNIT_ID(i)) != m_Player.lock())
		{
			um.GetPlayer(UNIT_ID(i))->DivMoveSpeedRate(0.5f);
		}
	}
}