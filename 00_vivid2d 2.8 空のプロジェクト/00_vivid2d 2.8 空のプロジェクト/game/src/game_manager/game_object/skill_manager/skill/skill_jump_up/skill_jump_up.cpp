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
SetPlayer(CPlayer* player)
{
	CSkill::SetPlayer(player);

	player->SetJumpPowerRate(m_jump_up_rate);
}

/*!
 *  @brief      �A�N�V�����Ăяo��
 */
void
CSkillJumpUp::
Action(void)
{

}