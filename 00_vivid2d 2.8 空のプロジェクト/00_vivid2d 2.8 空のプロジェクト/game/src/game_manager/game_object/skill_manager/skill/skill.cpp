#include "skill.h"

CSkill::CSkill(void)
{

}

CSkill::~CSkill(void)
{

}

/*!
 *  @brief      ������
 */
void CSkill::Initialize(CPlayer* player)
{
	m_Player = player;
	m_Player->SetSkill(this);
}

/*!
 *  @brief      �X�V
 */
void CSkill::Update(void)
{

}

/*!
 *  @brief      �`��
 */
void CSkill::Draw(void)
{

}

/*!
 *  @brief      ���
 */
void CSkill::Finalize(void)
{

}

/*!
 *  @brief      �A�N�V�����Ăяo��
 */
void CSkill::Action(void)
{

}
