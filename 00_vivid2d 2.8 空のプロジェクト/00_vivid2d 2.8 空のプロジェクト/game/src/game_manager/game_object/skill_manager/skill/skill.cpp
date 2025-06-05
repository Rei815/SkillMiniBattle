#include "skill.h"

const float				CSkill::m_icon_scale = 0.25;

const vivid::Vector2	CSkill::m_icon_positionList[] =
{
	vivid::Vector2( 256, 630),		//Player1
	vivid::Vector2( 512, 630),		//Player2
	vivid::Vector2( 768, 630),		//Player3
	vivid::Vector2(1024, 630)		//Player4
};

CSkill::CSkill(float duration_time, float cool_time)
	: m_SkillID(SKILL_ID::MAX)
	, m_State(SKILL_STATE::WAIT)
	, m_DurationTime(duration_time)
	, m_CoolTime(cool_time)
	, m_Timer(duration_time)
	, m_GaugePercent(0)
	, m_PlayerID(UNIT_ID::NONE)
	, m_IconPosition(vivid::Vector2::ZERO)
	, m_Category(SKILL_CATEGORY::PASSIVE)
	, m_UiSkillIcon(nullptr)
	, m_UiSkillGauge(nullptr)
	, m_UiSkillCursor(nullptr)
	,m_Sound(SE_ID::SKILL)
{

}

CSkill::CSkill(SKILL_CATEGORY category, float duration_time, float cool_time)
	: m_SkillID(SKILL_ID::MAX)
	, m_State(SKILL_STATE::WAIT)
	, m_DurationTime(duration_time)
	, m_CoolTime(cool_time)
	, m_Timer(duration_time)
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
	m_State = SKILL_STATE::WAIT;
	m_Timer.SetUp(m_DurationTime);
	m_Sound = SE_ID::SKILL;

}

/*!
 *  @brief      更新
 */
void CSkill::Update(void)
{
	//スキル更新
	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;

	case SKILL_STATE::ACTIVE:
		if (m_DurationTime > 0)
		{

			m_Timer.Update();
			m_GaugePercent = (m_DurationTime - m_Timer.GetTimer()) / m_DurationTime * 100.0f;
			if (m_Timer.Finished())
			{
				m_Timer.SetUp(m_CoolTime);
				ActionEnd();
				m_State = SKILL_STATE::COOLDOWN;
			}
		}
		break;

	case SKILL_STATE::COOLDOWN:


		if (m_CoolTime > 0)
		{
			m_Timer.Update();
			m_GaugePercent = m_Timer.GetTimer() / m_CoolTime * 100.0f;
			if (m_Timer.Finished())
			{
				m_Timer.SetUp(m_DurationTime);
				m_State = SKILL_STATE::WAIT;
			}
		}
		break;
	}

	//UI更新
	if (m_Player != nullptr && !m_Player->GetDefeatFlag())
	{
		if (m_UiSkillIcon != nullptr)
		{
			//明るさ変更
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
	else
	{
		m_UiSkillIcon->SetBrightness(CSkillIcon::ICON_BRIGHTNESS::DARK);
		m_UiSkillGauge->SetPercent(0);
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
void CSkill::SetPlayer(std::shared_ptr<CPlayer> player)
{
	CUIManager& uim = CUIManager::GetInstance();
	std::shared_ptr<CUI> temp;
	temp = uim.Create(UI_ID::SKILL_ICON);
	m_UiSkillIcon = std::dynamic_pointer_cast<CSkillIcon>(temp);
	if (m_UiSkillIcon == nullptr)
		temp->Delete();

	temp = uim.Create(UI_ID::SKILL_CURSOR);
	m_UiSkillCursor = std::dynamic_pointer_cast<CSkillCursor>(temp);
	if (m_UiSkillCursor == nullptr)
		temp->Delete();

	temp = uim.Create(UI_ID::SKILL_GAUGE);
	m_UiSkillGauge = std::dynamic_pointer_cast<CSkillGauge>(temp);
	if (m_UiSkillGauge == nullptr)
		temp->Delete();

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

/*!
 *  @brief      アクション終了
 */
void CSkill::ActionEnd(void)
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

SKILL_STATE CSkill::GetState(void)
{
	return m_State;
}

void CSkill::SetState(SKILL_STATE state)
{
	if(m_State != SKILL_STATE::COOLDOWN)
		m_State = state;
}
