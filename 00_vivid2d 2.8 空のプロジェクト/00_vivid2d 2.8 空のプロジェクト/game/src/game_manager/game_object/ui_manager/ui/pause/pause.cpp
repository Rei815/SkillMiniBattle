#include "pause.h"
#include "../../../unit_manager/unit_manager.h"

const vivid::Vector2    CPause::m_position = vivid::Vector2(0, 0);
const int    CPause::m_width = 1280;
const int    CPause::m_height = 780;

/*
 *  �R���X�g���N�^
 */
CPause::
CPause(void)
    : CUI(m_width, m_height)
{
}

/*
 *  �f�X�g���N�^
 */
CPause::
~CPause(void)
{
}

/*
 *  ������
 */
void
CPause::
Initialize(void)
{
    m_UI_ID = UI_ID::PAUSE;
    m_Attributes.push_back(UI_ATTRIBUTE::BUTTON);
    m_Position = m_position;
}

/*
 *  �X�V
 */
void
CPause::
Update(void)
{

}

/*
 *  �`��
 */
void
CPause::
Draw(void)
{
    vivid::DrawTexture("data\\Textures\\pause_bg.png", m_position, 0x80ffffff);

    vivid::DrawText(30, "�ꎞ��~��", vivid::Vector2(vivid::WINDOW_WIDTH / 2.0f - (vivid::GetTextWidth(30, "�ꎞ��~��") / 2), vivid::WINDOW_HEIGHT / 2.0f));

}

/*
 *  ���
 */
void
CPause::
Finalize(void)
{
}
