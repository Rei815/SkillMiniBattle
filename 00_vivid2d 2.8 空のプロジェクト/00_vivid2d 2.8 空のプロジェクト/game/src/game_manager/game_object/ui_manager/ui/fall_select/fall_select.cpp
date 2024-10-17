#include "fall_select.h"
#include "../../../unit_manager/unit_manager.h"

const vivid::Vector2    CFallSelect::m_position = vivid::Vector2(0, 0);
const int               CFallSelect::m_height = 368;
const int               CFallSelect::m_width = 368;
const vivid::Rect       CFallSelect::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CFallSelect::m_scale = vivid::Vector2(0.5f, 0.5f);
const vivid::Vector2    CFallSelect::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);

/*
 *  コンストラクタ
 */
CFallSelect::
CFallSelect(UI_ID id)
    : CUI(m_width, m_height)
	, m_UIID(id)
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
	switch (m_UIID)
	{
	case UI_ID::FALL_CIRCLE:	m_FileName = "data\\Textures\\fall_circle.png";		break;
	case UI_ID::FALL_MOON:		m_FileName = "data\\Textures\\fall_moon.png";		break;
	case UI_ID::FALL_CROSS:		m_FileName = "data\\Textures\\fall_cross.png";		break;
	case UI_ID::FALL_SUN:		m_FileName = "data\\Textures\\fall_sun.png";		break;
	case UI_ID::FALL_SQUARE:	m_FileName = "data\\Textures\\fall_square.png";		break;
	case UI_ID::FALL_TRIANGLE:	m_FileName = "data\\Textures\\fall_triangle.png";	break;
	}
}

/*
 *  更新
 */
void
CFallSelect::
Update(void)
{

}

/*
 *  描画
 */
void
CFallSelect::
Draw(void)
{
    vivid::DrawTexture(m_FileName, m_position, 0xffffffff, m_rect, m_anchor, m_scale);

}

/*
 *  解放
 */
void
CFallSelect::
Finalize(void)
{
}
