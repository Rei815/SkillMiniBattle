#include "scene_ui_parent.h"
#include "../../../scene_manager/scene_manager.h"
#include "../../ui_manager.h"

const vivid::Vector2    CSceneUIParent::m_position = vivid::Vector2(vivid::GetWindowWidth() / 2, -vivid::GetWindowHeight() / 2);
const int               CSceneUIParent::m_speed = 10;
const float             CSceneUIParent::m_max_height = vivid::GetWindowHeight() * 1.5;
const float             CSceneUIParent::m_min_height =  - vivid::GetWindowHeight() / 2;
const float             CSceneUIParent::m_wait_height = vivid::GetWindowHeight() / 2;

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
    //作られた時点で全てのUIを子にする
    m_ChildrenList.clear();
    CUI::Initialize(position);
    m_Transform.position.x = position.x;
    m_Transform.position.y = position.y;
    m_Velocity.y = m_speed;
    CUIManager::UI_LIST uiList = CUIManager::GetInstance().GetList();
    CUIManager::UI_LIST::iterator it = uiList.begin();
    while (it != uiList.end())
    {
        std::shared_ptr<CUI> ui = *it;
        ++it;
        if (ui->GetUI_ID() == UI_ID::TITLE_LOGO)        continue;

        if (ui->GetUI_ID() == UI_ID::SCENE_UI_PARENT)   continue;

        if (ui->GetParent() != nullptr)                 continue;

        if (ui->GetSceneID() != CSceneManager::GetInstance().GetLastSceneID()) continue;

        int offsetHeight;
        if (position.y > 0) offsetHeight = vivid::GetWindowHeight() * -1;
        else if (position.y < 0) offsetHeight = vivid::GetWindowHeight();
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
        ui->SetParent(shared_from_this());
        m_ChildrenList.emplace_back(ui);
    }
}

/*
 *  更新
 */
void CSceneUIParent::Update(void)
{
    CHILDREN_LIST::iterator it = m_ChildrenList.begin();
    while (it != m_ChildrenList.end())
    {
        std::shared_ptr<CUI> ui = *it;
        if (ui->GetParent() == nullptr || ui->IsActive() == false || ui == nullptr)
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
    CHILDREN_LIST::iterator it = m_ChildrenList.begin();
    while (it != m_ChildrenList.end())
    {
        (*it)->Delete();
        ++it;
    }
    m_ChildrenList.clear();

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
    CHILDREN_LIST::iterator it = m_ChildrenList.begin();
    while (it != m_ChildrenList.end())
    {
        std::shared_ptr<CUI> ui = *it;
        ui->SetParent(nullptr);
        ++it;
    }

}