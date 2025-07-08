#include "title_button.h"

const int    CTitleButton::m_width = 800;
const int    CTitleButton::m_height = 200;
const vivid::Vector2    CTitleButton::m_position = vivid::Vector2(vivid::GetWindowWidth() / 2 - m_width / 2, vivid::GetWindowHeight() / 2 + m_height / 2);
const int    CTitleButton::m_fade_speed = 2;

/*
 *  �R���X�g���N�^
 */
CTitleButton::
CTitleButton(UI_ID id)
    : CUI(m_width, m_height, id)
    , m_Color(0xffffffff)
    , m_FadeSpeed(m_fade_speed)
{
}

/*
 *  �f�X�g���N�^
 */
CTitleButton::
~CTitleButton(void)
{
}

/*
 *  ������
 */
void
CTitleButton::
Initialize(void)
{
    CUI::Initialize(m_position);
}

/*
 *  �X�V
 */
void
CTitleButton::
Update(void)
{
    CUI::Update();
    unsigned int alpha = vivid::alpha::GetAlpha(m_Color);
    if (alpha == 255u || alpha == 255u / 2)
        m_FadeSpeed = -m_FadeSpeed;
    m_Color = vivid::alpha::AdjustAlpha(m_Color, m_FadeSpeed);

}

/*
 *  �`��
 */
void
CTitleButton::
Draw(void)
{
    vivid::DrawTexture("data\\Textures\\title_button_ui.png", m_Position, m_Color);


}

/*
 *  ���
 */
void
CTitleButton::
Finalize(void)
{
}
