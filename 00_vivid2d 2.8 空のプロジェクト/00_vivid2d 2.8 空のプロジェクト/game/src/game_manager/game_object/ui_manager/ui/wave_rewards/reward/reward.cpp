#include "reward.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../unit_manager/unit/player/player.h"
#include "../../../ui_manager.h"

const int               CReward::m_height = 298;
const int               CReward::m_width = 295;

/*
 *  コンストラクタ
 */
CReward::
CReward(const std::string text)
    : CUI(m_width, m_height)
    , m_OnClick(false)
    , m_Text(text)
{
}

/*
 *  デストラクタ
 */
CReward::
~CReward(void)
{
}

/*
 *  初期化
 */
void
CReward::
Initialize(const vivid::Vector2& position)
{
    m_Position = position;
    m_Attributes.push_back(UI_ATTRIBUTE::BUTTON);

}

/*
 *  更新
 */
void
CReward::
Update(const vivid::Vector2& position, float offset)
{
    m_Position = vivid::Vector2(position.x + offset, position.y);
    if (OnMouseClick(m_Position, m_width, m_height))
    {
        m_OnClick = true;
        CUIManager::GetInstance().SetReceivedReward(true);

    }
}
/*
 *  描画
 */
void
CReward::
Draw()
{
    vivid::DrawTexture("data\\Textures\\reward.png", vivid::Vector2(m_Position.x - m_width / 2.0f, m_Position.y));

    vivid::DrawText(30, m_Text, vivid::Vector2(m_Position.x - vivid::GetTextWidth(30, m_Text) / 2.0f, m_Position.y + m_height / 2.0f));
    //DxLib::DrawBox(m_Position.x - m_width / 2.0f, m_Position.y, m_Position.x + m_width / 2.0f, m_Position.y + m_height, 0xffffffff, false);
}

/*
 *  解放
 */
void
CReward::Finalize(void)
{
}

