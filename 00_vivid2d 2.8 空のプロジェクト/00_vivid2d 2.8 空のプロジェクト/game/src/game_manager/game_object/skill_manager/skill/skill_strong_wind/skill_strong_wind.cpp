#include "skill_strong_wind.h"
#include "../../../unit_manager/unit_manager.h"

const float CSkillStrongWind::m_wind_strength = 1.5f;

CSkillStrongWind::CSkillStrongWind(void)
	:CSkill()
{

}

CSkillStrongWind::~CSkillStrongWind(void)
{

}

/*!
 *  @brief      初期化
 */
void
CSkillStrongWind::
Initialize(CPlayer* player)
{
	CSkill::Initialize(player);
}

/*!
 *  @brief      更新
 */
void
CSkillStrongWind::
Update(void)
{
	CSkill::Update();


}

/*!
 *  @brief      描画
 */
void
CSkillStrongWind::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CSkillStrongWind::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      アクション呼び出し
 */
void
CSkillStrongWind::
Action(void)
{
	CVector3 velocity = m_Player->GetVelocity();
	velocity.z -= m_wind_strength;
	m_Player->SetVelocity(velocity);

}