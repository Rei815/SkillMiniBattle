#include "skill_resurrect_belt.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../object_manager/object_manager.h"
#include "../../../sound_manager/sound_manager.h"

const CVector3	CSkillResurrectBelt::m_resurrect_position = CVector3(0.0f,500.0f,0.0f);
const float		CSkillResurrectBelt::m_effect_scale = 2.0f;

CSkillResurrectBelt::CSkillResurrectBelt(void)
	:CSkill(SKILL_CATEGORY::PASSIVE)
	, m_ResurrectEffect(nullptr)
	, m_SkillEffect(nullptr)

{

}

CSkillResurrectBelt::~CSkillResurrectBelt(void)
{

}

/*!
 *  @brief      ������
 */
void
CSkillResurrectBelt::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

/*!
 *  @brief      �X�V
 */
void
CSkillResurrectBelt::
Update(void)
{
	CSkill::Update();

	CObjectManager::OBJECT_LIST objectList = CObjectManager::GetInstance().GetList();
	CObjectManager::OBJECT_LIST::iterator it = objectList.begin();
	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;

	case SKILL_STATE::ACTIVE:
		CSoundManager::GetInstance().Play_SE(SE_ID::RESURECT, false);
		m_Player.lock()->SetPosition(m_resurrect_position);

		if (m_SkillEffect == nullptr)
		{
			m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, CVector3().ZERO, CVector3(), m_effect_scale);
			m_ResurrectEffect = CEffectManager::GetInstance().Create(EFFECT_ID::RESURRECT, CVector3().ZERO, CVector3(), m_effect_scale);
			m_SkillEffect->SetParent(m_Player.lock());
			m_ResurrectEffect->SetParent(m_Player.lock());
		}
		m_State = SKILL_STATE::COOLDOWN;
		break;

	case SKILL_STATE::COOLDOWN:
		break;
	}
}

/*!
 *  @brief      �`��
 */
void
CSkillResurrectBelt::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      ���
 */
void
CSkillResurrectBelt::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      �A�N�V�����Ăяo��
 */
void
CSkillResurrectBelt::
Action()
{
}

/*!
 *  @brief      �A�N�V�����I��
 */
void
CSkillResurrectBelt::
ActionEnd(void)
{
	if (m_SkillEffect != nullptr)
	{
		m_SkillEffect->SetActive(false);
		m_SkillEffect = nullptr;
	}
	if (m_ResurrectEffect != nullptr)
	{
		m_ResurrectEffect->SetActive(false);
		m_ResurrectEffect = nullptr;
	}
}