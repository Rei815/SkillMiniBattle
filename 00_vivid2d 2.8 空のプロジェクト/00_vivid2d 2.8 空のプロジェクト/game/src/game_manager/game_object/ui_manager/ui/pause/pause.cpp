#include "pause.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../controller_manager/controller_manager.h"
#include "../../../scene_manager/scene_manager.h"

const int    CPause::m_width = 861;
const int    CPause::m_height = 181;
const vivid::Vector2    CPause::m_position = vivid::Vector2(vivid::GetWindowWidth() / 2 - m_width / 2, vivid::GetWindowHeight() / 2 + m_height / 2);
const vivid::Vector2    CPause::m_offset = vivid::Vector2(0, -200);
const vivid::Rect       CPause::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CPause::m_scale = vivid::Vector2(0.8f, 0.8f);
const vivid::Vector2    CPause::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);

/*
 *  �R���X�g���N�^
 */
CPause::
CPause(UI_ID id)
    : CUI(m_width, m_height, id)
    , m_UINum(0)
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
    m_Position = m_position;
    for (int i = 0; i < 2; i++)
    {
        m_Color[i] = 0xffffffff;
        m_Scale[i] = m_scale;
        m_Anchor[i] = m_anchor;
    }
    SetPosition(m_position);
    m_Scale[0] = vivid::Vector2(1.0f, 1.0f);
    m_Scale[1] = m_scale;
    m_Color[1] = 0xff808080;
    m_Color[0] = 0xffffffff;

}

/*
 *  �X�V
 */
void
CPause::
Update(void)
{
#ifdef _DEBUG
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::W))
    {
        m_UINum = 0;
        m_Scale[m_UINum] = vivid::Vector2(1.0f, 1.0f);
        m_Scale[1] = m_scale;
        m_Color[1] = 0xff808080;
        m_Color[m_UINum] = 0xffffffff;
    }
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S))
    {
        m_UINum = 1;
        m_Scale[m_UINum] = vivid::Vector2(1.0f, 1.0f);
        m_Scale[0] = m_scale;
        m_Color[0] = 0xff808080;
        m_Color[m_UINum] = 0xffffffff;
    }
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
    {
        CSceneManager& sm = CSceneManager::GetInstance();

        if (m_UINum == 0)
            sm.Pause();
        else if (m_UINum == 1)
        {
            sm.SetPauseFlag(false);
            sm.ChangeScene(SCENE_ID::TITLE);
        }

    }

#endif // _DEBUG

    vivid::Vector2 stick = vivid::Vector2::ZERO;
    if (m_PauseController != nullptr)
    {
        stick = m_PauseController->GetLeftStick();
        if ((stick.y < -0.5f && !m_PauseController->GetLeftVertical()) || stick.y == -1.0f)
        {
            m_PauseController->SetLeftVertical(true);
            m_UINum = 0;
            m_Scale[m_UINum] = vivid::Vector2(1.0f, 1.0f);
            m_Scale[1] = m_scale;
            m_Color[1] = 0xff808080;
            m_Color[m_UINum] = 0xffffffff;
        }
        if ((stick.y > 0.5f && !m_PauseController->GetLeftVertical()) || stick.y == 1.0f)
        {
            m_PauseController->SetLeftVertical(true);
        
            m_UINum = 1;
            m_Scale[m_UINum] = vivid::Vector2(1.0f, 1.0f);
            m_Scale[0] = m_scale;
            m_Color[0] = 0xff808080;
            m_Color[m_UINum] = 0xffffffff;
        }
        if (m_PauseController->GetButtonDown(BUTTON_ID::B))
        {
            CSceneManager& sm = CSceneManager::GetInstance();

            if (m_UINum == 0)
                sm.Pause();
            else if (m_UINum == 1)
            {
                sm.SetPauseFlag(false);
                sm.ChangeScene(SCENE_ID::TITLE);
            }
        }
    }

}

/*
 *  �`��
 */
void
CPause::
Draw(void)
{
    vivid::DrawTexture("data\\Textures\\pause_bg.png", vivid::Vector2::ZERO, 0x80ffffff);
    vivid::DrawTexture("data\\Textures\\pause_start.png", m_position + m_offset, m_Color[0], m_rect, m_anchor, m_Scale[0]);
    vivid::DrawTexture("data\\Textures\\pause_return_title.png", m_position, m_Color[1], m_rect, m_anchor, m_Scale[1]);
}

/*
 *  ���
 */
void
CPause::
Finalize(void)
{
}

void CPause::SetPauseController(CController* controller)
{
    m_PauseController = controller;
}
