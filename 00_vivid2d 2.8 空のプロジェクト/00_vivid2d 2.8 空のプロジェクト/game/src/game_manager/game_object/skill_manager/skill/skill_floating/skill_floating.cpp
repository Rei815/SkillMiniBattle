#include "skill_floating.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../sound_manager/sound_manager.h"

const float		CSkillFloating::m_duration_time = 5.0f;
const float		CSkillFloating::m_cool_time = 10.0f;
const CVector3	CSkillFloating::m_scale = CVector3(4.0f, 1.0f, 4.0f);
const float		CSkillFloating::m_effect_scale = 2.0;

CSkillFloating::CSkillFloating(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
	, m_Effect(nullptr)
	, m_SkillEffect(nullptr)
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
		CVector3 effectPosition = m_Player.lock()->GetPosition();
		effectPosition.y -= m_Player.lock()->GetHeight() / 2;
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

	CSoundManager::GetInstance().Play_SE(SE_ID::FLOATING, false);
	CVector3 velocity = m_Player.lock()->GetVelocity();

	m_Player.lock()->SetGravity(CVector3::ZERO);
	m_Player.lock()->SetVelocity(CVector3(velocity.x, 0.1f, velocity.z));
	m_Player.lock()->SetParent(nullptr);
	m_Player.lock()->SetIsGround(false);
	CVector3 effectPosition = m_Player.lock()->GetPosition();
	effectPosition.y -= m_Player.lock()->GetHeight() / 2;

	m_Effect = CEffectManager::GetInstance().Create(EFFECT_ID::FLOATING, effectPosition, CVector3::UP, m_scale);
	m_State = SKILL_STATE::ACTIVE;

	m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, effectPosition, CVector3(), m_effect_scale);
	m_SkillEffect->SetParent(m_Player.lock());

}

/*!
 *  @brief      アクション終了
 */
void
CSkillFloating::
ActionEnd(void)
{
	m_Player.lock()->SetGravity(m_Player.lock()->GetDefaultGravity());
	if (m_Effect != nullptr )
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
		