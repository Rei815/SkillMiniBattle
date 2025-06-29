#include "skill_stomp.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../../../component/model_component/model_component.h"

const float CSkillStomp::m_cool_time = 10.0f;
const float CSkillStomp::m_effect_scale = 2.0f;

CSkillStomp::CSkillStomp(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, 0.0f, m_cool_time)
	,m_SkillEffect(nullptr)
{

}

CSkillStomp::~CSkillStomp(void)
{

}

/*!
 *  @brief      初期化
 */
void
CSkillStomp::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
	m_GameObject->AddComponent<ModelComponent>(MODEL_ID::STOMP_COLL);

}

/*!
 *  @brief      更新
 */
void
CSkillStomp::
Update(void)
{
	CSkill::Update();
	m_GameObject->Update(vivid::GetDeltaTime());

}

/*!
 *  @brief      描画
 */
void
CSkillStomp::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CSkillStomp::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      アクション呼び出し
 */
void
CSkillStomp::
Action()
{
	
	if (m_State == SKILL_STATE::COOLDOWN) return;

	CSoundManager::GetInstance().Play_SE(SE_ID::STOMP, false);
	CBulletManager::GetInstance().Create(m_Player.lock()->GetUnitCategory(), BULLET_ID::SHOCK_WAVE, m_Player.lock()->GetPosition(), CVector3::UP);
	CEffectManager::GetInstance().Create(EFFECT_ID::SHOCK_WAVE, m_Player.lock()->GetPosition());
	m_Timer.SetUp(m_cool_time);
	m_State = SKILL_STATE::COOLDOWN;

	m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, CVector3().ZERO, CVector3(), m_effect_scale);
	m_SkillEffect->SetParent(m_Player.lock());
}

/*!
 *  @brief      アクション終了
 */
void
CSkillStomp::
ActionEnd(void)
{
	if (m_SkillEffect != nullptr)
	{
		m_SkillEffect->Delete();
		m_SkillEffect = nullptr;
	}
}