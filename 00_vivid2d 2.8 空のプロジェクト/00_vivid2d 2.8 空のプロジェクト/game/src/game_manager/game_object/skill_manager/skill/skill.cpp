#include "skill.h"

CSkill::CSkill(void)
{

}

CSkill::~CSkill(void)
{

}

/*!
 *  @brief      初期化
 */
void CSkill::Initialize(CPlayer* player)
{
	m_Player = player;
	m_Player->SetSkill(this);
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
 *  @brief      アクション呼び出し
 */
void CSkill::Action(void)
{

}
