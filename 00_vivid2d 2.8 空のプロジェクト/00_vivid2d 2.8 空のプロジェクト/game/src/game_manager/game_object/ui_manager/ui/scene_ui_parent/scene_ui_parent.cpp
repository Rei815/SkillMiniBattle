#include "scene_ui_parent.h"
#include "../../../unit_manager/unit_manager.h"

const vivid::Vector2      CSceneUIParent::m_position = vivid::Vector2(vivid::GetWindowWidth() /2, -vivid::GetWindowHeight() / 2);
const int           CSceneUIParent::m_speed = 5;

/*
 *  コンストラクタ
 */
CSceneUIParent::CSceneUIParent(UI_ID id)
    : CUI(id)
{
}

/*
 *  デストラクタ
 */
CSceneUIParent::~CSceneUIParent(void)
{
}

/*
 *  初期化
 */
void CSceneUIParent::Initialize()
{
    CUI::Initialize(m_position);
    m_Transform.position.x = m_position.x;
    m_Transform.position.y = m_position.y;
    m_Velocity.y = m_speed;
    CUIManager::UI_LIST uiList = CUIManager::GetInstance().GetList();
    CUIManager::UI_LIST::iterator it = uiList.begin();
    while (it != uiList.end())
    {
        CUI* ui = (CUI*)(*it);
        ++it;
        if (ui->GetUI_ID() == UI_ID::TITLE_LOGO) continue;
        const int offsetHeight = vivid::GetWindowHeight();
        CTransform transform = ui->GetTransform();
        transform.position.y += offsetHeight;
        vivid::Vector2 position = ui->GetPosition();
        position.y -= offsetHeight;
        ui->SetPosition(position);
        ui->SetTransform(transform);
        ui->SetParent(this);
    }
}

/*
 *  更新
 */
void CSceneUIParent::Update(void)
{
    m_Position.y += m_Velocity.y;
    m_Transform.position -= m_Velocity;

    if (m_Position.y >= vivid::GetWindowHeight() / 2)
    {
        m_Velocity.y = 0;
    }
}

/*
 *  描画
 */
void CSceneUIParent::Draw(void)
{
}

/*
 *  解放
 */
void
CSceneUIParent::Finalize(void)
{
}
