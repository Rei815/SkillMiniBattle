#include "skill.h"

const float				CSkill::m_icon_scale = 0.25;

const vivid::Vector2	CSkill::m_icon_positionList[] =
{
	vivid::Vector2( 256, 630),		//Player1
	vivid::Vector2( 512, 630),		//Player2
	vivid::Vector2( 768, 630),		//Player3
	vivid::Vector2(1024, 630)		//Player4
};

CSkill::CSkill(void)
	: m_SkillID(SKILL_ID::MAX)
	, m_State(SKILL_STATE::WAIT)
	, m_GaugePercent(0)
	, m_PlayerID(UNIT_ID::NONE)
	, m_IconPosition(vivid::Vector2::ZERO)
	, m_Category(SKILL_CATEGORY::PASSIVE)
	, m_UiSkillIcon(nullptr)
	, m_UiSkillGauge(nullptr)
	, m_UiSkillCursor(nullptr)
{

}

CSkill::CSkill(SKILL_CATEGORY category)
	: m_SkillID(SKILL_ID::MAX)
	, m_State(SKILL_STATE::WAIT)
	, m_GaugePercent(0)
	, m_PlayerID(UNIT_ID::NONE)
	, m_IconPosition(vivid::Vector2::ZERO)
	, m_Category(category)
	, m_UiSkillIcon(nullptr)
	, m_UiSkillGauge(nullptr)
	, m_UiSkillCursor(nullptr)
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
	CUIManager& uim = CUIManager::GetInstance();

	CUI* temp;

	temp = uim.Create(UI_ID::SKILL_ICON);
	m_UiSkillIcon = dynamic_cast<CSkillIcon*>(temp);
	if (m_UiSkillIcon == nullptr)
		temp->SetActive(false);

	temp = uim.Create(UI_ID::SKILL_CURSOR);
	m_UiSkillCursor = dynamic_cast<CSkillCursor*>(temp);
	if (m_UiSkillCursor == nullptr)
		temp->SetActive(false);

	temp = uim.Create(UI_ID::SKILL_GAUGE);
	m_UiSkillGauge = dynamic_cast<CSkillGauge*>(temp);
	if (m_UiSkillGauge == nullptr)
		temp->SetActive(false);
}

/*!
 *  @brief      更新
 */
void CSkill::Update(void)
{
	if (m_UiSkillIcon != nullptr)
	{
		//明るさ変更（未実装）
		switch (m_State)
		{
		case SKILL_STATE::WAIT:
		case SKILL_STATE::ACTIVE:
			m_UiSkillIcon->SetBrightness(CSkillIcon::ICON_BRIGHTNESS::BRIGHT);
			break;
		case SKILL_STATE::COOLDOWN:
			m_UiSkillIcon->SetBrightness(CSkillIcon::ICON_BRIGHTNESS::DARK);
			break;
		}
	}

	if (m_UiSkillGauge != nullptr)
	{
		m_UiSkillGauge->SetPercent(m_GaugePercent);
	}
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

	m_PlayerID = m_Player->GetUnitID();
	m_IconPosition = m_icon_positionList[(int)m_PlayerID];

	if (m_UiSkillIcon != nullptr)
	{
		m_UiSkillIcon->SetIcon(m_SkillID, m_IconPosition, m_icon_scale);
	}

	if (m_UiSkillCursor != nullptr)
	{
		m_UiSkillCursor->SetCursor(m_PlayerID, m_IconPosition, m_icon_scale);
	}

	if (m_UiSkillGauge != nullptr)
	{
		m_UiSkillGauge->SetGauge(m_IconPosition, m_icon_scale);
	}
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