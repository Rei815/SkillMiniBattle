#include "skill_jump_up.h"
#include "../../../../../game/components/player_component/player_component.h"
const float CSkillJumpUp::m_jump_up_rate = 1.1f;

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
SetPlayer(std::shared_ptr<CGameObject> player)
{
	CSkill::SetPlayer(player);
	auto playerComp = player->GetComponent<PlayerComponent>();
	playerComp->SetJumpPowerRate(m_jump_up_rate);
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