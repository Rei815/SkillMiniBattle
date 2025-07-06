#include "skill_jump_up.h"
#include "../../../../../game/components/player_component/player_component.h"
const float CSkillJumpUp::m_jump_up_rate = 1.4f;

CSkillJumpUp::CSkillJumpUp(void)
	:CSkill(SKILL_CATEGORY::PASSIVE)
{

}

CSkillJumpUp::~CSkillJumpUp(void)
{

}

/*!
 *  @brief      ������
 */
void
CSkillJumpUp::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);

	m_State = SKILL_STATE::WAIT;
}

/*!
 *  @brief      �X�V
 */
void
CSkillJumpUp::
Update(void)
{
	CSkill::Update();


}

/*!
 *  @brief      �`��
 */
void
CSkillJumpUp::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      ���
 */
void
CSkillJumpUp::
Finalize(void)
{
	CSkill::Finalize();


}

/*!
 *  @brief      �v���C���[�̃Z�b�g
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
 *  @brief      �A�N�V�����Ăяo��
 */
void
CSkillJumpUp::
Action(void)
{

}

/*!
 *  @brief      �A�N�V�����I��
 */
void
CSkillJumpUp::
ActionEnd(void)
{

}