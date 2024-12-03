#include "skill_speed_up.h"
#include "../../../unit_manager/unit_manager.h"

const float CSkillSpeedUp::m_speed_up_rate = 1.25f;

CSkillSpeedUp::CSkillSpeedUp(void)
	:CSkill()
{

}

CSkillSpeedUp::~CSkillSpeedUp(void)
{

}

/*!
 *  @brief      初期化
 */
void
CSkillSpeedUp::
Initialize(CPlayer* player)
{
	CSkill::Initialize(player);

	player->SetMoveSpeedRate(m_speed_up_rate);
}

/*!
 *  @brief      更新
 */
void
CSkillSpeedUp::
Update(void)
{
	CSkill::Update();


}

/*!
 *  @brief      描画
 */
void
CSkillSpeedUp::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CSkillSpeedUp::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      アクション呼び出し
 */
void
CSkillSpeedUp::
Action(void)
{

}