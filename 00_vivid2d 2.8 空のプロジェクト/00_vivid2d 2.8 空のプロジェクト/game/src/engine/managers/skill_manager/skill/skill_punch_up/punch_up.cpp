#include "punch_up.h"

CPunchUp::CPunchUp(void)
	:CSkill(SKILL_CATEGORY::PASSIVE)
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

/*!
 *  @brief      �A�N�V�����I��
 */
void
CPunchUp::
ActionEnd(void)
{

}