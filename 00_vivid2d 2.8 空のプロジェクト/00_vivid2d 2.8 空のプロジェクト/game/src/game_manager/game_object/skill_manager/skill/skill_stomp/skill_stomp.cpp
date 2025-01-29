#include "skill_stomp.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../sound_manager/sound_manager.h"

const float CSkillStomp::m_cool_time = 10.0f;

CSkillStomp::CSkillStomp(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, 0.0f, m_cool_time)
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
}

/*!
 *  @brief      更新
 */
void
CSkillStomp::
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
	CBulletManager::GetInstance().Create(m_Player->GetUnitCategory(), BULLET_ID::SHOCK_WAVE, m_Player->GetPosition(), CVector3::UP);
	CEffectManager::GetInstance().Create(EFFECT_ID::SHOCK_WAVE, m_Player->GetPosition());
	m_State = SKILL_STATE::COOLDOWN;
}

/*!
 *  @brief      アクション終了
 */
void
CSkillStomp::
ActionEnd(void)
{

}