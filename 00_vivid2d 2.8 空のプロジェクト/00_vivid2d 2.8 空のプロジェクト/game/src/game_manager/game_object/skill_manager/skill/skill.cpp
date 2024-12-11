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
 *  @brief      初期化
 */
void CSkill::Initialize(SKILL_ID skill_id)
{
	m_SkillID = skill_id;
}

/*!
 *  @brief      更新
 */
void CSkill::Update(void)
{

}

/*!
 *  @brief      描画
 */
void CSkill::Draw(void)
{

}

/*!
 *  @brief      解放
 */
void CSkill::Finalize(void)
{

}

/*!
 *  @brief      プレイヤーのセット
 */
void CSkill::SetPlayer(CPlayer* player)
{
	m_Player = player;
	m_Player->SetSkill(this);
}

/*!
 *  @brief      アクション呼び出し
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