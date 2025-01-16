#include "skill_jump_up.h"
#include "../../../unit_manager/unit_manager.h"

const float CSkillJumpUp::m_jump_up_rate = 1.5f;

CSkillJumpUp::CSkillJumpUp(void)
	:CSkill(SKILL_CATEGORY::PASSIVE)
{

}

CSkillJumpUp::~CSkillJumpUp(void)
{

}

/*!
 *  @brief      初期化
 */
void
CSkillJumpUp::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);

	m_State = SKILL_STATE::WAIT;
}

/*!
 *  @brief      更新
 */
void
CSkillJumpUp::
Update(void)
{
	CSkill::Update();


}

/*!
 *  @brief      描画
 */
void
CSkillJumpUp::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CSkillJumpUp::
Finalize(void)
{
	CSkill::Finalize();


}

/*!
 *  @brief      プレイヤーのセット
 */
void
CSkillJumpUp::
SetPlayer(CPlayer* player)
{
	CSkill::SetPlayer(player);

	player->SetJumpPowerRate(m_jump_up_rate);
}

/*!
 *  @brief      アクション呼び出し
 */
void
CSkillJumpUp::
Action(void)
{

}

/*!
 *  @brief      アクション終了
 */
void
CSkillJumpUp::
ActionEnd(void)
{

}