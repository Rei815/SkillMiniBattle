#include "fall_select.h"
#include "../../../unit_manager/unit_manager.h"

const vivid::Vector2    CFallSelect::m_positionList[] = { vivid::Vector2(0, 0),vivid::Vector2(200, 0),vivid::Vector2(400, 0),
vivid::Vector2(600, 0),vivid::Vector2(800, 0),vivid::Vector2(1000, 0) };
const int               CFallSelect::m_height = 1107;
const int               CFallSelect::m_width = 200;
const vivid::Rect       CFallSelect::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CFallSelect::m_scale = vivid::Vector2(0.5f, 0.5f);
const vivid::Vector2    CFallSelect::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);
const float				CFallSelect::m_speed = 1.0f;

/*
 *  コンストラクタ
 */
CFallSelect::
CFallSelect(UI_ID id)
    : CUI(m_width, m_height, id)
	, m_BackGround(UI_ID::FALLOUT_SELECT_BG)
{
}

/*
 *  デストラクタ
 */
CFallSelect::
~CFallSelect(void)
{
}

/*
 *  初期化
 */
void
CFallSelect::
Initialize(void)
{
	switch (m_UI_ID)
	{
	case UI_ID::FALL_CIRCLE:	m_FileName = "data\\Textures\\fall_circle_ui.png";		break;
	case UI_ID::FALL_MOON:		m_FileName = "data\\Textures\\fall_moon_ui.png";		break;
	case UI_ID::FALL_CROSS:		m_FileName = "data\\Textures\\fall_cross_ui.png";		break;
	case UI_ID::FALL_SUN:		m_FileName = "data\\Textures\\fall_sun_ui.png";		break;
	case UI_ID::FALL_SQUARE:	m_FileName = "data\\Textures\\fall_square_ui.png";		break;
	case UI_ID::FALL_TRIANGLE:	m_FileName = "data\\Textures\\fall_triangle_ui.png";	break;
	}
	m_Position = m_positionList[(int)m_UI_ID - 2];
	m_BackGround.Initialize(m_Position);
	m_Rect = m_rect;

}

/*
 *  更新
 */
void
CFallSelect::
Update(void)
{
	m_Position.y += m_speed;
	m_Rect.top -= m_speed;
}

/*
 *  描画
 */
void
CFallSelect::
Draw(void)
{
	m_BackGround.Draw();
    vivid::DrawTexture(m_FileName, m_Position + vivid::Vector2(77.0f, 25.0f), 0xffffffff, m_rect, m_anchor, m_scale);
}

/*
 *  解放
 */
void
CFallSelect::
Finalize(void)
{
}