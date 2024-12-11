#include "skill_gauge.h"
#include "../../../unit_manager/unit/unit_id.h"

const vivid::Vector2    CSkillGauge::m_positionList[] = 
	{
		vivid::Vector2(100, 700),		//Player1
		vivid::Vector2(367, 700),		//Player2
		vivid::Vector2(633, 700),		//Player3
		vivid::Vector2(900, 700)		//Player4
	};

const int               CSkillGauge::m_height = 384;
const int               CSkillGauge::m_width = 384;
/*
const vivid::Rect       CSkillGauge::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CSkillGauge::m_scale = vivid::Vector2(0.5f, 0.5f);
const vivid::Vector2    CSkillGauge::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);
*/

const std::string       CSkillGauge::m_file_name = "data\\Textures\\skill_gauge_test.png";
const double            CSkillGauge::m_start_percent = 0.0;
const double            CSkillGauge::m_scale = 0.5f;

/*
 *  コンストラクタ
 */
CSkillGauge::
CSkillGauge(UI_ID id)
	: CUI(m_width, m_height, id)
	, m_ImageHandle(0)
	, m_Percent(0)
{
}

/*
 *  デストラクタ
 */
CSkillGauge::
~CSkillGauge(void)
{
}

/*
 *  初期化
 */
void
CSkillGauge::
Initialize(void)
{
	CUI::Initialize();

	m_ImageHandle = LoadGraph(m_file_name.c_str());
	m_Percent = 0;
}

/*
 *  更新
 */
void
CSkillGauge::
Update(void)
{
	CUI::Update();
}

/*
 *  描画
 */
void
CSkillGauge::
Draw(void)
{
	CUI::Draw();

	DrawCircleGauge(m_Position.x,m_Position.y,m_Percent,m_ImageHandle,m_start_percent,m_scale);
}

/*
 *  解放
 */
void
CSkillGauge::
Finalize(void)
{
	CUI::Finalize();
}


void
CSkillGauge::
SetIcon(int PosNum)
{
	if (PosNum >= 0 && PosNum < (int)UNIT_ID::NONE)
		m_Position = m_positionList[PosNum];
	else
		m_Position = vivid::Vector2().ZERO;
}


void
CSkillGauge::
SetGauge(float percent)
{
	m_Percent = (double)percent;
}