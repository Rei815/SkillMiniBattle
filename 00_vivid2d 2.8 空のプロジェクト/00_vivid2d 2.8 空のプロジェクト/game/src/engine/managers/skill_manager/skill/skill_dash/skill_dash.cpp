#include "skill_dash.h"
#include "../../../../components/transform_component/transform_component.h"
#include "../../../../../game/components/player_component/player_component.h"
const float CSkillDash:: m_dash_speed_up_rate = 5.0f;
const float CSkillDash:: m_duration_time = 0.35f;
const float CSkillDash:: m_cool_time = 5.0f;

CSkillDash::CSkillDash(void)
	: CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
	, m_SkillEffect(nullptr)
{

}

CSkillDash::~CSkillDash(void)
{

}

/*!
 *  @brief      初期化
 */
void
CSkillDash::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

/*!
 *  @brief      更新
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
 *  @brief      描画
 */
void
CSkillDash::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CSkillDash::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      アクション呼び出し
 */
void
CSkillDash::
Action(void)
{
	if (m_State != SKILL_STATE::WAIT)
		return;

	CSoundManager::GetInstance().Play_SE(SE_ID::DASH, false);

	CVector3 effectPosition = m_Player.lock()->GetComponent<TransformComponent>()->GetPosition();

	m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, 
		CVector3().ZERO, CVector3(), 3.0f);
	m_SkillEffect->SetParent(m_Player.lock());


	m_Player.lock()->GetComponent<PlayerComponent>()->MulMoveSpeedRate(m_dash_speed_up_rate);
	m_State = SKILL_STATE::ACTIVE;
}

/*!
 *  @brief      アクション終了
 */
void
CSkillDash::
ActionEnd(void)
{
	if (m_SkillEffect != nullptr)
	{
		m_SkillEffect->Delete();
		m_SkillEffect = nullptr;
	}

	m_Player.lock()->GetComponent<PlayerComponent>()->DivMoveSpeedRate(m_dash_speed_up_rate);
}