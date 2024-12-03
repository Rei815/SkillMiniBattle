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
 *  @brief      ������
 */
void
CSkillSpeedUp::
Initialize(CPlayer* player)
{
	CSkill::Initialize(player);

	player->SetMoveSpeedRate(m_speed_up_rate);
}

/*!
 *  @brief      �X�V
 */
void
CSkillSpeedUp::
Update(void)
{
	CSkill::Update();


}

/*!
 *  @brief      �`��
 */
void
CSkillSpeedUp::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      ���
 */
void
CSkillSpeedUp::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      �A�N�V�����Ăяo��
 */
void
CSkillSpeedUp::
Action(void)
{

}