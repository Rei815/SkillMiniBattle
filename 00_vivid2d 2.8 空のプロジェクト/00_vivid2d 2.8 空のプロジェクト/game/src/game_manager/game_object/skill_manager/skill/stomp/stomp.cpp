#include "stomp.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../../effect_manager/effect_manager.h"

const float CStomp::m_floating_time = 3.0f;

CStomp::CStomp(void)
	:CSkill(SKILL_CATEGORY::ACTIVE)
{

}

CStomp::~CStomp(void)
{

}

/*!
 *  @brief      初期化
 */
void
CStomp::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
	m_Category = SKILL_CATEGORY::ACTIVE;
}

/*!
 *  @brief      更新
 */
void
CStomp::
Update(void)
{
	CSkill::Update();
	if (m_Timer.Finished())
	{
		m_Timer.Reset();
	}
}

/*!
 *  @brief      描画
 */
void
CStomp::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CStomp::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      アクション呼び出し
 */
void
CStomp::
Action()
{

	CBulletManager::GetInstance().Create(m_Player->GetUnitCategory(), BULLET_ID::SHOCK_WAVE, m_Player->GetPosition(), CVector3::UP);
	CEffectManager::GetInstance().Create(EFFECT_ID::SHOCK_WAVE, m_Player->GetPosition());
}