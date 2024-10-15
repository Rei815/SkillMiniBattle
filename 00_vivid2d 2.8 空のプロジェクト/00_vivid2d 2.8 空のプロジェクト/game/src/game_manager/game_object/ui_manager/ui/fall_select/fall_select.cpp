#include "fall_select.h"
#include "../../../unit_manager/unit_manager.h"

const vivid::Vector2    CFallSelect::m_position = vivid::Vector2(0, vivid::GetWindowHeight() - m_height * 0.25f);
const int               CFallSelect::m_height = 256;
const int               CFallSelect::m_width = 256;
const vivid::Rect       CFallSelect::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CFallSelect::m_scale = vivid::Vector2(0.1f, 0.1f);
const vivid::Vector2    CFallSelect::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);

/*
 *  �R���X�g���N�^
 */
CFallSelect::
CFallSelect(UI_ID id)
    : CUI(m_width, m_height)
{
}

/*
 *  �f�X�g���N�^
 */
CFallSelect::
~CFallSelect(void)
{
}

/*
 *  ������
 */
void
CFallSelect::
Initialize(void)
{
	switch (m_UIID)
	{
	case UI_ID::FALL_CIRCLE:	m_FileName = "data\\Textures\\fall_circle";		break;
	case UI_ID::FALL_MOON:		m_FileName = "data\\Textures\\fall_moon";		break;
	case UI_ID::FALL_CROSS:		m_FileName = "data\\Textures\\fall_cross";		break;
	case UI_ID::FALL_SUN:		m_FileName = "data\\Textures\\fall_sun";		break;
	case UI_ID::FALL_SQUARE:	m_FileName = "data\\Textures\\fall_square";		break;
	case UI_ID::FALL_TRIANGLE:	m_FileName = "data\\Textures\\fall_triangle";	break;
	}
}

/*
 *  �X�V
 */
void
CFallSelect::
Update(void)
{

}

/*
 *  �`��
 */
void
CFallSelect::
Draw(void)
{
    vivid::DrawTexture(m_FileName, m_position, 0xffffffff, m_rect, m_anchor, m_scale);

}

/*
 *  ���
 */
void
CFallSelect::
Finalize(void)
{
}
