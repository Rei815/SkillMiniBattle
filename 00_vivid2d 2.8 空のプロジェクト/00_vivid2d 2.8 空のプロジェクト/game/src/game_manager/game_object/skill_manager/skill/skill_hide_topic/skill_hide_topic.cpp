#include "skill_hide_topic.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../ui_manager/ui_manager.h"
#include "../../../sound_manager/sound_manager.h"

const float CSkillHideTopic::m_cool_time = 5.0f;
const float CSkillHideTopic::m_duration_time = 5.0f;
const float CSkillHideTopic::m_effect_scale = 3.0f;

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
		if (m_ParentTopic)
		{
			m_Shutter->SetPosition(m_ParentTopic->GetPosition());
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

	CSoundManager::GetInstance().Play_SE(SE_ID::HIDETOPIC, false);
	CUIManager::UI_LIST uiList = CUIManager::GetInstance().GetList();
	CUIManager::UI_LIST topicList;
	CUIManager::UI_LIST::iterator it = uiList.begin();

	while (it != uiList.end())
	{
		CUI* ui = ((*it).get());
		if (ui->GetUI_ID() == UI_ID::FALLOUT_TOPIC_BG)
		{
			topicList.emplace_back(ui);
		}
		++it;
	}
	if (topicList.empty()) return;
	it = topicList.begin();
	int num = rand() % topicList.size();
	std::advance(it, num);
	m_ParentTopic = ((*it).get());
	m_Shutter = CUIManager::GetInstance().Create(UI_ID::TOPIC_SHUTTER, (*it)->GetPosition());
	m_State = SKILL_STATE::ACTIVE;

	CVector3 effect_position = m_Player->GetPosition();

	m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, effect_position, CVector3(), m_effect_scale);
	m_SkillEffect->SetParent(m_Player);
}

/*!
 *  @brief      アクション終了
 */
void
CSkillHideTopic::
ActionEnd(void)
{
	if (m_SkillEffect != nullptr)
	{
		m_SkillEffect->SetActive(false);
		m_SkillEffect = nullptr;
	}
}