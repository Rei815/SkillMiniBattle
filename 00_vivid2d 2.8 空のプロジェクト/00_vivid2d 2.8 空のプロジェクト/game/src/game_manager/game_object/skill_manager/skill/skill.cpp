#include "skill.h"

CSkill::CSkill(void)
	: m_SkillID(SKILL_ID::MAX)
	, m_Category(SKILL_CATEGORY::PASSIVE)
{

}

CSkill::CSkill(SKILL_CATEGORY category)
	: m_SkillID(SKILL_ID::MAX)
	, m_Category(category)
{
}

CSkill::~CSkill(void)
{

}

/*!
 *  @brief      ������
 */
void CSkill::Initialize(SKILL_ID skill_id)
{
	m_SkillID = skill_id;
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
 *  @brief      �v���C���[�̃Z�b�g
 */
void CSkill::SetPlayer(CPlayer* player)
{
	m_Player = player;
	m_Player->SetSkill(this);
}

/*!
 *  @brief      �A�N�V�����Ăяo��
 */
void CSkill::Action(void)
{

}

SKILL_CATEGORY CSkill::GetSkillCategory()
{
	return m_Category;
}

SKILL_ID CSkill::GetSkillID()
{
	return m_SkillID;
}