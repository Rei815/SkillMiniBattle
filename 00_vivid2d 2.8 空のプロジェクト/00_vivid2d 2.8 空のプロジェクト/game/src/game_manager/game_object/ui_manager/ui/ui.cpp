#include "ui.h"
#include "..\..\unit_manager\unit_manager.h"

/*
 *  コンストラクタ
 */
CUI::
CUI(int width, int height)
    : m_ActiveFlag(true)
    , m_Attributes{ CUI::UI_ATTRIBUTE::NONE }
    , m_Width(width)
    , m_Height(height)
{
}

/*
 *  デストラクタ
 */
CUI::
~CUI(void)
{
}

/*
 *  初期化
 */
void
CUI::
Initialize(void)
{
}

/*
 *  更新
 */
void
CUI::
Update(void)
{

}

/*
 *  描画
 */
void
CUI::
Draw(void)
{

}

/*
 *  解放
 */
void
CUI::
Finalize(void)
{
}

/*
 *  アクティブフラグ取得
 */
bool
CUI::
GetActive(void)
{
    return m_ActiveFlag;
}

/*
 *  アクティブフラグ設定
 */
void
CUI::
SetActive(bool active)
{
    m_ActiveFlag = active;
}

bool CUI::CheckAttribute(UI_ATTRIBUTE attribute)
{
    for (int i = 0; i < m_Attributes.size(); i++)
    {
        if (m_Attributes[i] == attribute)
            return true;
    }
    return false;
}

bool CUI::OnMouseClick(const vivid::Vector2& position, int width, int height)
{
    if (vivid::mouse::Trigger(vivid::mouse::BUTTON_ID::LEFT))
    {
        vivid::Point mouse_pos = vivid::mouse::GetCursorPos();
        if (position.x - width / 2.0f < mouse_pos.x && mouse_pos.x < position.x + width / 2.0f &&
            position.y < mouse_pos.y && mouse_pos.y < position.y + height)
            return true;
        else return false;
    }
}

vivid::Vector2 CUI::GetPosition(void)
{
    return m_Position;
}

int CUI::GetWidth(void)
{
    return m_Width;
}

int CUI::GetHeight(void)
{
    return m_Height;
}

UI_ID CUI::GetUI_ID(void)
{
    return m_UI_ID;
}

