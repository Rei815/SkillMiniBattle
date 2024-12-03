#include "skill_jump_up.h"
#include "../../../unit_manager/unit_manager.h"

const float CSkillJumpUp::m_jump_up_rate = 1.5f;

CSkillJumpUp::CSkillJumpUp(void)
	:CSkill()
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
Initialize(CPlayer* player)
{
	CSkill::Initialize(player);

	player->SetJumpPowerRate(m_jump_up_rate);
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
 *  @brief      �A�N�V�����Ăяo��
 */
void
CSkillJumpUp::
Action(void)
{

}