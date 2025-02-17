#include "skill_mimicry.h"
#include "../../../sound_manager/sound_manager.h"

const float CSkillMimicry::m_cool_time = 10.0f;
const float CSkillMimicry::m_duration_time = 5.0f;
const float CSkillMimicry::m_mimicry_speed_rate = 0.5f;
const float CSkillMimicry::m_effect_scale = 3.0f;

CSkillMimicry::CSkillMimicry(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
	,m_SkillEffect(nullptr)
{
}

CSkillMimicry::~CSkillMimicry(void)
{
}

void CSkillMimicry::Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

void CSkillMimicry::Update(void)
{
	CSkill::Update();

	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		m_Player->SetAlpha(1.0f);
		break;

	case SKILL_STATE::ACTIVE:
		m_Player->DecAlpha(0.5f);
		break;

	case SKILL_STATE::COOLDOWN:
		m_Player->RevertAlpha(1.0f);
		break;
	}
}

void CSkillMimicry::Draw(void)
{
	CSkill::Draw();
}

void CSkillMimicry::Finalize(void)
{
	CSkill::Finalize();
}

void CSkillMimicry::Action()
{
	if (m_State != SKILL_STATE::WAIT)	return;

	CSoundManager::GetInstance().Play_SE(SE_ID::MIMICRY, false);
	m_Player->MulMoveSpeedRate(m_mimicry_speed_rate);
	m_Player->StartInvincible(m_duration_time);
	m_State = SKILL_STATE::ACTIVE;
	CVector3 effect_position = m_Player->GetPosition();


	m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, effect_position, CVector3(), m_effect_scale);
	m_SkillEffect->SetParent(m_Player);
}

/*!
 *  @brief      アクション終了
 */
void CSkillMimicry::ActionEnd(void)
{
	m_Player->DivMoveSpeedRate(m_mimicry_speed_rate);
}
