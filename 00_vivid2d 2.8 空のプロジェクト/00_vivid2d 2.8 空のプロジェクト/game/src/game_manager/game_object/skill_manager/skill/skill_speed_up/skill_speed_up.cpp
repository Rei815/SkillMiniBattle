#include "skill_speed_up.h"
#include "../../../unit_manager/unit_manager.h"

const float CSkillSpeedUp::m_speed_up_rate = 1.25f;

CSkillSpeedUp::CSkillSpeedUp(void)
	:CSkill(SKILL_CATEGORY::PASSIVE)
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
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);

	m_State = SKILL_STATE::WAIT;
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
 *  @brief      プレイヤーのセット
 */
void
CSkillSpeedUp::
SetPlayer(CPlayer* player)
{
	CSkill::SetPlayer(player);

	player->SetMoveSpeedRate(m_speed_up_rate);
}

/*!
 *  @brief      アクション呼び出し
 */
void
CSkillSpeedUp::
Action(void)
{

}