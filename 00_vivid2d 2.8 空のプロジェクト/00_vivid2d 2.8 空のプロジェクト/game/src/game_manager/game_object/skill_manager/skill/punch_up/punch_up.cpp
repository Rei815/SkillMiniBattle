#include "punch_up.h"
#include "../../../unit_manager/unit_manager.h"

const float CPunchUp::speed_up_rate = 1.25f;

CPunchUp::CPunchUp(void)
	:CSkill()
{

}

CPunchUp::~CPunchUp(void)
{

}

/*!
 *  @brief      ������
 */
void
CPunchUp::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);

	//player->SetMoveSpeedRate(speed_up_rate);
}

/*!
 *  @brief      �X�V
 */
void
CPunchUp::
Update(void)
{
	CSkill::Update();


}

/*!
 *  @brief      �`��
 */
void
CPunchUp::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      ���
 */
void
CPunchUp::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      �A�N�V�����Ăяo��
 */
void
CPunchUp::
Action(void)
{

}