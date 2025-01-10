#include "skill_hide_topic.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../ui_manager/ui_manager.h"

const float CSkillHideTopic::m_cool_time = 5.0f;
const float CSkillHideTopic::m_duration_time = 5.0f;

CSkillHideTopic::CSkillHideTopic(void)
	:CSkill(SKILL_CATEGORY::ACTIVE)
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
	m_Timer.SetUp(m_duration_time);
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
		m_Timer.Update();
		m_GaugePercent = (m_duration_time - m_Timer.GetTimer()) / m_duration_time * 100.0f;

		if (m_Timer.Finished())
		{
			m_Timer.SetUp(m_cool_time);
			m_State = SKILL_STATE::COOLDOWN;
		}
		break;
	case SKILL_STATE::COOLDOWN:
		m_Timer.Update();

		m_GaugePercent = m_Timer.GetTimer() / m_cool_time * 100.0f;

		if (m_Timer.Finished())
			m_State = SKILL_STATE::WAIT;

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
	m_Timer.SetUp(m_duration_time);
	CUIManager::UI_LIST uiList = CUIManager::GetInstance().GetList();
	CUIManager::UI_LIST topicList;
	CUIManager::UI_LIST::iterator it = uiList.begin();

	while (it != uiList.end())
	{
		CUI* ui = (*it);
		if (ui->GetUI_ID() == UI_ID::FALLOUT_TOPIC)
		{
			topicList.push_back(ui);
		}
		++it;
	}
	if (topicList.empty()) return;
	it = topicList.begin();
	int num = rand() % topicList.size();
	std::advance(it, num);
	CUIManager::GetInstance().Create(UI_ID::TOPIC_SHUTTER, (*it)->GetPosition());
	m_State = SKILL_STATE::ACTIVE;
}