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

    switch (m_State)
    {
    case CSceneUIParent::STATE::WAIT:
        m_Velocity = CVector3::ZERO;
        break;
    case CSceneUIParent::STATE::SCENE_IN:
        if (m_Position.y >= vivid::GetWindowHeight() / 2)
        {
            m_Position.y = vivid::GetWindowHeight() / 2;
            m_Velocity.y = 0;
        }
        break;
    case CSceneUIParent::STATE::SCENE_OUT:
        break;
    case CSceneUIParent::STATE::BACK:
        break;
    default:
        break;
    }
    m_Position.y += m_Velocity.y;
    m_Transform.position -= m_Velocity;

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

void CSceneUIParent::SetState(STATE state)
{
    m_State = state;
}
