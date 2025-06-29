#include "skill_resurrect_daruma.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../data_manager/data_manager.h"
#include "../../../sound_manager/sound_manager.h"

const float CSkillResurrectDaruma::m_duration_time = 2.0f;
const float CSkillResurrectDaruma::m_effect_scale = 2.0f;

CSkillResurrectDaruma::CSkillResurrectDaruma(void)
	:CSkill(SKILL_CATEGORY::PASSIVE, m_duration_time)
	, m_SkillEffect(nullptr)
	, m_ResurrectEffect(nullptr)
	, m_EffectFlag(false)
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
		if (m_EffectFlag == false)
		{
			m_EffectFlag = true;
			m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, CVector3().ZERO, CVector3(), m_effect_scale);
			m_ResurrectEffect = CEffectManager::GetInstance().Create(EFFECT_ID::RESURRECT, CVector3().ZERO, CVector3(), m_effect_scale);
			m_SkillEffect->SetParent(m_Player.lock());
			m_ResurrectEffect->SetParent(m_Player.lock());
		}

		break;
	case SKILL_STATE::COOLDOWN:
		CSoundManager::GetInstance().Play_SE(SE_ID::RESURECT, false);
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
	m_Player.lock()->SetActionFlag(true);

	if (m_SkillEffect != nullptr)
	{
		m_SkillEffect->Delete(false);
		m_SkillEffect = nullptr;
	}

	if (m_ResurrectEffect != nullptr)
	{
		m_ResurrectEffect->Delete(false);
		m_ResurrectEffect = nullptr;
	}
}
