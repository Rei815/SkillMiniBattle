#include "jump_up.h"
#include "../../../unit_manager/unit_manager.h"

const float CJumpUp::jump_up_rate = 1.5f;

CJumpUp::CJumpUp(void)
	:CSkill()
{

}

CJumpUp::~CJumpUp(void)
{

}

/*!
 *  @brief      ������
 */
void
CJumpUp::
Initialize(CPlayer* player)
{
	CSkill::Initialize(player);

	player->SetJumpPowerRate(jump_up_rate);
}

/*!
 *  @brief      �X�V
 */
void
CJumpUp::
Update(void)
{
	CSkill::Update();


}

/*!
 *  @brief      �`��
 */
void
CJumpUp::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      ���
 */
void
CJumpUp::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      �A�N�V�����Ăяo��
 */
void
CJumpUp::
Action(void)
{

}