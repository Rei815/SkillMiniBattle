#include "skill_dash.h"
#include "../../../unit_manager/unit_manager.h"


const float CSkillDash::m_dash_speed_up_rate = 5.0f;
const float CSkillDash:: m_duration_time = 0.35f;
const float CSkillDash:: m_cool_time = 5.0f;

CSkillDash::CSkillDash(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
	, m_SkillEffect(nullptr)

{

}

CSkillDash::~CSkillDash(void)
{

}

/*!
 *  @brief      ������
 */
void
CSkillDash::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

/*!
 *  @brief      �X�V
 */
void
CSkillDash::
Update(void)
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

/*!
 *  @brief      �`��
 */
void
CSkillDash::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      ���
 */
void
CSkillDash::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      �A�N�V�����Ăяo��
 */
void
CSkillDash::
Action(void)
{
	if (m_State != SKILL_STATE::WAIT)
		return;

	CSoundManager::GetInstance().Play_SE(SE_ID::DASH, false);

	CVector3 effectPosition = m_Player->GetPosition();
	//effectPosition.y -= m_Player->GetHeight() / 2;

	m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, 
		effectPosition, CVector3(), 3.0f);

	m_Player->MulMoveSpeedRate(m_dash_speed_up_rate);
	m_State = SKILL_STATE::ACTIVE;
}

/*!
 *  @brief      �A�N�V�����I��
 */
void
CSkillDash::
ActionEnd(void)
{
	if (m_SkillEffect != nullptr)
	{
		m_SkillEffect->SetActive(false);
		m_SkillEffect = nullptr;
	}

	m_Player->DivMoveSpeedRate(m_dash_speed_up_rate);
}