#include "skill_floating.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../effect_manager/effect_manager.h"

const float		CSkillFloating::m_duration_time = 5.0f;
const float		CSkillFloating::m_cool_time = 10.0f;
const CVector3	CSkillFloating::m_scale = CVector3(4.0f, 1.0f, 4.0f);

CSkillFloating::CSkillFloating(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
	, m_Effect(nullptr)

{

}

CSkillFloating::~CSkillFloating(void)
{

}

/*!
 *  @brief      初期化
 */
void
CSkillFloating::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

/*!
 *  @brief      更新
 */
void
CSkillFloating::
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

	if (m_Effect != nullptr)
	{
		CVector3 effectPosition = m_Player->GetPosition();
		effectPosition.y -= m_Player->GetHeight() / 2;
		m_Effect->SetPosition(effectPosition);
	}
}

/*!
 *  @brief      描画
 */
void
CSkillFloating::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CSkillFloating::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      アクション呼び出し
 */
void
CSkillFloating::
Action()
{
	if (m_State != SKILL_STATE::WAIT) return;

	CVector3 velocity = m_Player->GetVelocity();

	m_Player->SetGravity(CVector3::ZERO);
	m_Player->SetVelocity(CVector3(velocity.x, 0.0f, velocity.z));
	m_Player->SetParent(nullptr);
	m_Player->SetIsGround(false);
	CVector3 effectPosition = m_Player->GetPosition();
	effectPosition.y -= m_Player->GetHeight() / 2;

	m_Effect = CEffectManager::GetInstance().Create(EFFECT_ID::FLOATING, effectPosition, CVector3::UP, m_scale);
	m_State = SKILL_STATE::ACTIVE;
}

/*!
 *  @brief      アクション終了
 */
void
CSkillFloating::
ActionEnd(void)
{
	m_Player->SetGravity(m_Player->GetDefaultGravity());
	if (m_Effect != nullptr)
		m_Effect->SetActive(false);
}