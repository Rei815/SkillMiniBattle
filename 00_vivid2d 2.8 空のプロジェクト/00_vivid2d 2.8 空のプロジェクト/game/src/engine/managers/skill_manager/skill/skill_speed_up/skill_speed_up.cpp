#include "skill_speed_up.h"
#include "../../../../../game/components/player_component/player_component.h"

const float CSkillSpeedUp::m_speed_up_rate = 1.25f;

CSkillSpeedUp::CSkillSpeedUp(void)
	:CSkill(SKILL_CATEGORY::PASSIVE)
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
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);

	m_State = SKILL_STATE::WAIT;
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
 *  @brief      �v���C���[�̃Z�b�g
 */
void
CSkillSpeedUp::
SetPlayer(std::shared_ptr<CGameObject> player)
{
	CSkill::SetPlayer(player);

	player->GetComponent<PlayerComponent>()->SetMoveSpeedRate(m_speed_up_rate);
}

/*!
 *  @brief      �A�N�V�����Ăяo��
 */
void
CSkillSpeedUp::
Action(void)
{

}

/*!
 *  @brief      �A�N�V�����I��
 */
void
CSkillSpeedUp::
ActionEnd(void)
{

}