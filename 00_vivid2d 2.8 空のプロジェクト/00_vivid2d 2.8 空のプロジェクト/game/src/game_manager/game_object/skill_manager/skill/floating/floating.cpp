#include "floating.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../effect_manager/effect_manager.h"

const float		CFloating::m_floating_time = 3.0f;
const float		CFloating::m_cool_time = 3.0f;
const CVector3	CFloating::m_scale = CVector3(4.0f, 1.0f, 4.0f);

CFloating::CFloating(void)
	:CSkill(SKILL_CATEGORY::ACTIVE)
	, m_Effect(nullptr)

{

}

CFloating::~CFloating(void)
{

}

/*!
 *  @brief      初期化
 */
void
CFloating::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);

	m_State = SKILL_STATE::WAIT;
}

/*!
 *  @brief      更新
 */
void
CFloating::
Update(void)
{
	CSkill::Update();
	m_SkillDuration.Update();

	if (m_SkillDuration.Finished())
	{
		m_SkillDuration.AllReset();
		m_Player->SetGravity(m_Player->GetDefaultGravity());
		m_CoolTime.Update();
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
CFloating::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CFloating::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      アクション呼び出し
 */
void
CFloating::
Action(UNIT_CATEGORY category)
{
	if (m_CoolTime.Finished() == false) return;

	m_SkillDuration.SetUp(m_floating_time);
	m_CoolTime.SetUp(m_cool_time);
	CVector3 velocity = m_Player->GetVelocity();

	m_Player->SetGravity(CVector3::ZERO);
	m_Player->SetVelocity(CVector3(velocity.x, 0.0f, velocity.z));

	CVector3 effectPosition = m_Player->GetPosition();
	effectPosition.y -= m_Player->GetHeight() / 2;

	m_Effect = CEffectManager::GetInstance().Create(EFFECT_ID::FLOATING, effectPosition, CVector3::UP, m_scale);
}