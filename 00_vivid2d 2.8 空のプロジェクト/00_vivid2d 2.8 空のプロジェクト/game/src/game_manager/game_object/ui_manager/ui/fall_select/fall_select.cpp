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
CFallSelect(void)
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
    vivid::DrawTexture("data\\Textures\\player_life.png", m_position, 0xffffffff, m_rect, m_anchor, m_scale);

}

/*
 *  ���
 */
void
CFallSelect::
Finalize(void)
{
}
