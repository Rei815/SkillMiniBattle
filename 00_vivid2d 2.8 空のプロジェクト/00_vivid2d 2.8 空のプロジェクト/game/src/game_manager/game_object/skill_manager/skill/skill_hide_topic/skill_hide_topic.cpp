#include "skill_hide_topic.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../ui_manager/ui_manager.h"

const float CSkillHideTopic::m_cool_time = 5.0f;
const float CSkillHideTopic::m_duration_time = 5.0f;

CSkillHideTopic::CSkillHideTopic(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
{

}

CSkillHideTopic::~CSkillHideTopic(void)
{

}

/*!
 *  @brief      初期化
 */
void
CSkillHideTopic::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

/*!
 *  @brief      更新
 */
void
CSkillHideTopic::
Update(void)
{
	CSkill::Update();

	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;
	case SKILL_STATE::ACTIVE:
		if (m_Parent)
		{
			m_Shutter->SetPosition(m_Parent->GetPosition());
		}
		break;
	case SKILL_STATE::COOLDOWN:
		break;
	}

}

/*!
 *  @brief      描画
 */
void
CSkillHideTopic::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CSkillHideTopic::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      アクション呼び出し
 */
void
CSkillHideTopic::
Action(void)
{
	if (m_State != SKILL_STATE::WAIT) return;

	CUIManager::UI_LIST uiList = CUIManager::GetInstance().GetList();
	CUIManager::UI_LIST topicList;
	CUIManager::UI_LIST::iterator it = uiList.begin();

	while (it != uiList.end())
	{
		CUI* ui = (*it);
		if (ui->GetUI_ID() == UI_ID::FALLOUT_TOPIC_BG)
		{
			topicList.push_back(ui);
		}
		++it;
	}
	if (topicList.empty()) return;
	it = topicList.begin();
	int num = rand() % topicList.size();
	std::advance(it, num);
	m_Parent = (*it);
	m_Shutter = CUIManager::GetInstance().Create(UI_ID::TOPIC_SHUTTER, (*it)->GetPosition());
	m_State = SKILL_STATE::ACTIVE;
}

/*!
 *  @brief      アクション終了
 */
void
CSkillHideTopic::
ActionEnd(void)
{

}