#include "skill_ogre_control.h"
#include "../../../object_manager/object_manager.h"

const float CSkillOgreControl::m_cool_time = 30.0f;
const float CSkillOgreControl::m_duration_time = 10.0f;
const float CSkillOgreControl::m_effect_scale = 2.0f;
const CVector3 CSkillOgreControl::m_EffectPosition = CVector3(1500, 100, 10);

CSkillOgreControl::CSkillOgreControl(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
	,m_SkillEffect(nullptr)
{
}


CSkillOgreControl::~CSkillOgreControl(void)
{
}

void CSkillOgreControl::Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
	m_Target = nullptr;
	
}

void CSkillOgreControl::Update(void)
{
	CSkill::Update();

	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;

	case SKILL_STATE::ACTIVE:
		if (!m_Player->GetPlayerMoving())
		{
			m_Gimmick->OgreControlTurn();
			m_State = SKILL_STATE::COOLDOWN;
			m_Timer.SetUp(m_cool_time);
		}
		break;

	case SKILL_STATE::COOLDOWN:
		if (m_Effect != nullptr)
		{
			m_Effect->SetActive(false);
			m_Effect = nullptr;
		}
		break;
	}
}

void CSkillOgreControl::Draw(void)
{
	CSkill::Draw();
}

void CSkillOgreControl::Finalize(void)
{
	CSkill::Finalize();
}

void CSkillOgreControl::Action()
{
	if (m_State == SKILL_STATE::WAIT)
	{
		m_Effect = CEffectManager::GetInstance().Create(EFFECT_ID::OGRE_CONTROL, m_EffectPosition, CVector3(), 5.0f);

		m_Gimmick = dynamic_cast<CDaruma_FallDownGimmick*>((*CObjectManager::GetInstance().GetList().begin())->GetGimmick());
		m_State = SKILL_STATE::ACTIVE;

		m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, CVector3().ZERO, CVector3(), m_effect_scale);
		m_SkillEffect->SetParent(m_Player);
	}
}

/*!
 *  @brief      アクション終了
 */
void CSkillOgreControl::ActionEnd(void)
{
	if (m_Effect != nullptr)
	{
		m_Effect->SetActive(false);
		m_Effect = nullptr;
	}

	if (m_SkillEffect != nullptr)
	{
		m_SkillEffect->SetActive(false);
		m_SkillEffect = nullptr;
	}
}