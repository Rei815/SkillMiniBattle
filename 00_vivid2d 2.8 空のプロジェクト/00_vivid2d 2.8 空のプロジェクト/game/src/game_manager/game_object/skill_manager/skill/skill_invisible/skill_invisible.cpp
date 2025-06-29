#include "skill_invisible.h"
#include "../../../sound_manager/sound_manager.h"

const float CSkillInvisible::m_cool_time = 10.0f;
const float CSkillInvisible::m_duration_time = 3.0f;
const float CSkillInvisible::m_effect_scale = 3.0f;

CSkillInvisible::CSkillInvisible(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
	, m_Active(false)
	, m_SkillEffect(nullptr)
{
}

CSkillInvisible::~CSkillInvisible(void)
{
}

void CSkillInvisible::Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

void CSkillInvisible::Update(void)
{
	CSkill::Update();

	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		m_Player.lock()->SetAlpha(1.0f);
		break;

	case SKILL_STATE::ACTIVE:
		m_Player.lock()->DecAlpha(0.5f);
		break;

	case SKILL_STATE::COOLDOWN:
		m_Player.lock()->RevertAlpha(1.0f);
		break;
	}
}

void CSkillInvisible::Draw(void)
{
	CSkill::Draw();
}

void CSkillInvisible::Finalize(void)
{
	CSkill::Finalize();
}

void CSkillInvisible::Action(void)
{
	if (m_State != SKILL_STATE::WAIT) return;

	CSoundManager::GetInstance().Play_SE(SE_ID::INVISIBLE, false);
	m_Player.lock()->StartInvincible(m_duration_time);
	m_State = SKILL_STATE::ACTIVE;

	CVector3 effect_position = m_Player.lock()->GetPosition();

	m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, effect_position, CVector3(), m_effect_scale);
	m_SkillEffect->SetParent(m_Player.lock());
}

/*!
 *  @brief      アクション終了
 */
void CSkillInvisible::ActionEnd(void)
{
	if (m_SkillEffect != nullptr)
	{
		m_SkillEffect->Delete(false);
		m_SkillEffect = nullptr;
	}
}