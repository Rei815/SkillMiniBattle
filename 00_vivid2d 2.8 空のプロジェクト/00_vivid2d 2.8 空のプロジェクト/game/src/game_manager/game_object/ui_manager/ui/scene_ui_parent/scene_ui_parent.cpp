#include "scene_ui_parent.h"
#include "../../../scene_manager/scene_manager.h"
#include "../../ui_manager.h"

const vivid::Vector2      CSceneUIParent::m_position = vivid::Vector2(vivid::GetWindowWidth() / 2, -vivid::GetWindowHeight() / 2);
const int           CSceneUIParent::m_speed = 10;
const float            CSceneUIParent::m_max_height = vivid::GetWindowHeight() * 1.5;
const float           CSceneUIParent::m_min_height =  - vivid::GetWindowHeight() / 2;
const float           CSceneUIParent::m_wait_height = vivid::GetWindowHeight() / 2;

/*
 *  コンストラクタ
 */
CSceneUIParent::CSceneUIParent(UI_ID id)
    : CUI(id)
    , m_State(STATE::NONE)
    , m_WaitFlag(false)
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
void CSceneUIParent::Initialize(const vivid::Vector2& position)
{
    m_ChildrenList.clear();
    CUI::Initialize(position);
    m_Transform.position.x = position.x;
    m_Transform.position.y = position.y;
    m_Velocity.y = m_speed;
    CUIManager::UI_LIST uiList = CUIManager::GetInstance().GetList();
    CUIManager::UI_LIST::iterator it = uiList.begin();
    while (it != uiList.end())
    {
        CUI* ui = (CUI*)(*it);
        ++it;
        if (ui->GetUI_ID() == UI_ID::TITLE_LOGO)        continue;

        if (ui->GetUI_ID() == UI_ID::SCENE_UI_PARENT)   continue;

        if (ui->GetParent() != nullptr)                 continue;

        if (ui->GetSceneID() != CSceneManager::GetInstance().GetLastSceneID()) continue;

        int offsetHeight = vivid::GetWindowHeight() * -((position.y > 0) - (position.y < 0));
        if(m_Position.y == vivid::GetWindowHeight() / 2)
        {
            offsetHeight = 0;
            m_WaitFlag = true;
        }
        //3D版
        CTransform transform = ui->GetTransform();
        transform.position.y += offsetHeight;

        //2D版
        vivid::Vector2 position = ui->GetPosition();
        position.y -= offsetHeight;

        ui->SetPosition(position);
        ui->SetTransform(transform);
        ui->SetParent(this);
        m_ChildrenList.push_back(ui);
    }
}

/*
 *  更新
 */
void CSceneUIParent::Update(void)
{
    CHILDRENLIST::iterator it = m_ChildrenList.begin();
    while (it != m_ChildrenList.end())
    {
        CUI* ui = (CUI*)(*it);
        if (ui->GetParent() == nullptr || ui->GetActive() == false || ui == nullptr)
        {
           it = m_ChildrenList.erase(it);
           continue;
        }
        ++it;
    }

    m_Position.y += m_Velocity.y;
    m_Transform.position -= m_Velocity;

    if ((m_Position.y <= m_min_height || m_max_height <= m_Position.y) && m_WaitFlag == true)
    {
        m_Velocity.y = 0;
        m_State = STATE::FINISH;
    }
    switch (m_State)
    {
    case CSceneUIParent::STATE::WAIT:
        m_Velocity = CVector3::ZERO;
        break;
    case CSceneUIParent::STATE::MOVE_ONE:
        if (m_Position.y + m_speed >= m_wait_height && m_WaitFlag == false)
        {
            m_Velocity.y = m_wait_height - m_Position.y;
        }
        if (m_Position.y >= m_wait_height && m_WaitFlag == false)
        {
            m_WaitFlag = true;
            m_Position.y = m_wait_height;
            m_Velocity.y = 0;
            m_State = STATE::WAIT;
        }
        break;
    case CSceneUIParent::STATE::BACK_ONE:
        if (m_Position.y + m_speed <= m_wait_height && m_WaitFlag == false)
        {
            m_Velocity.y = m_Position.y - m_wait_height;
        }
        if (m_Position.y <= m_wait_height && m_WaitFlag == false)
        {
            m_WaitFlag = true;
            m_Position.y = m_wait_height;
            m_Velocity.y = 0;
            m_State = STATE::WAIT;
        }
        break;
    case CSceneUIParent::STATE::FINISH:
        m_Velocity = CVector3::ZERO;
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
    CHILDRENLIST::iterator it = m_ChildrenList.begin();
    while (it != m_ChildrenList.end())
    {
        (*it)->SetActive(false);
        ++it;
    }
}

CSceneUIParent::STATE CSceneUIParent::GetState(void)
{
    return m_State;
}

void CSceneUIParent::SetState(STATE state)
{
    m_State = state;
    switch (state)
    {
    case CSceneUIParent::STATE::WAIT:
        m_Velocity = CVector3::ZERO;
        break;
    case CSceneUIParent::STATE::MOVE_ONE:
        m_Velocity.y = m_speed;
        break;
    case CSceneUIParent::STATE::BACK_ONE:
        m_Velocity.y = -m_speed;
        break;
    }
}

void CSceneUIParent::ReleaseChildren()
{
    CHILDRENLIST::iterator it = m_ChildrenList.begin();
    while (it != m_ChildrenList.end())
    {
        CUI* ui = (CUI*)(*it);
        ui->SetParent(nullptr);
        ++it;
    }

}