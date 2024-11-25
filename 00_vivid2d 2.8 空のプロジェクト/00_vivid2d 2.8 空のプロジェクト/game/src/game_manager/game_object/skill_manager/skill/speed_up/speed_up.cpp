#include "speed_up.h"
#include "../../../unit_manager/unit_manager.h"

const float CSpeedUp::speed_up_rate = 1.5f;

CSpeedUp::CSpeedUp(void)
	:CSkill()
{

}

CSpeedUp::~CSpeedUp(void)
{

}

/*!
 *  @brief      ������
 */
void
CSpeedUp::
Initialize(CPlayer* player)
{
	CSkill::Initialize(player);

	player->SetMoveSpeedRate(speed_up_rate);
}

/*!
 *  @brief      �X�V
 */
void
CSpeedUp::
Update(void)
{
	CSkill::Update();


}

/*!
 *  @brief      �`��
 */
void
CSpeedUp::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      ���
 */
void
CSpeedUp::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      �A�N�V�����Ăяo��
 */
void
CSpeedUp::
Action(void)
{

}