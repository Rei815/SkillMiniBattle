#include "controller_manager.h"

/*
 *  インスタンスの取得
 */
CControllerManager& CControllerManager::GetInstance(void)
{
    static CControllerManager instance;

    return instance;
}

/*
 *  初期化
 */
void
CControllerManager::Initialize(void)
{
    m_ControllerNum = vivid::controller::GetConnectCount();
    m_ControllerList.clear();
    Create(CONTROLLER_ID::ONE);
    Create(CONTROLLER_ID::TWO);
    Create(CONTROLLER_ID::THREE);
    Create(CONTROLLER_ID::FOUR);

}

/*
 *  更新
 */
void
CControllerManager::Update(void)
{
    if (m_ControllerList.empty()) return;

    CONTROLLER_LIST::iterator it = m_ControllerList.begin();

    while (it != m_ControllerList.end())
    {
        CController* controller = (CController*)(*it);

        controller->Update();

        if (!controller->GetActive())
        {
            controller->Finalize();

            delete controller;

            it = m_ControllerList.erase(it);

            continue;
        }

        ++it;
    }

}



/*
 *  解放
 */
void
CControllerManager::Finalize(void)
{
    if (m_ControllerList.empty()) return;

    CONTROLLER_LIST::iterator it = m_ControllerList.begin();

    while (it != m_ControllerList.end())
    {
        (*it)->Finalize();

        delete (*it);

        ++it;
    }

    m_ControllerList.clear();

}

void CControllerManager::SetControllerNum(int num)
{
    m_ControllerNum = num;
}

int CControllerManager::GetControllerNum()
{
    return m_ControllerNum;
}

CController* CControllerManager::Create(CONTROLLER_ID id)
{
    CController* controller = nullptr;

    controller = new CController();


    if (!controller) return nullptr;

    controller->Initialize(id);

    m_ControllerList.push_back(controller);

    return controller;
}

CController* CControllerManager::GetController(CONTROLLER_ID controller_id)
{
    if (m_ControllerList.empty()) return nullptr;

    CONTROLLER_LIST::iterator it = m_ControllerList.begin();

    while (it != m_ControllerList.end())
    {
        if ((*it)->GetID() == controller_id)
            return (*it);

        ++it;
    }

    return nullptr;
}

bool CControllerManager::GetAnyControllerButtonDown(BUTTON_ID button_id)
{
    if (m_ControllerList.empty()) return false;

    CONTROLLER_LIST::iterator it = m_ControllerList.begin();

    while (it != m_ControllerList.end())
    {
        if ((*it)->GetButtonDown(button_id) == true)
            return true;

        ++it;
    }

    return false;
}

void CControllerManager::Vibration(CONTROLLER_ID controller_id)
{
    if (m_ControllerList.empty()) return;

    CONTROLLER_LIST::iterator it = m_ControllerList.begin();

    while (it != m_ControllerList.end())
    {
        CController* controller = (CController*)(*it);
        if (controller->GetID() == controller_id)
            controller->Vibration();

        ++it;
    }

}

CController* CControllerManager::GetSpecifiedButtonDownController(BUTTON_ID button_id)
{
    if (m_ControllerList.empty()) return nullptr;

    CONTROLLER_LIST::iterator it = m_ControllerList.begin();

    while (it != m_ControllerList.end())
    {
        if ((*it)->GetButtonDown(button_id) == true)
            return (*it);

        ++it;
    }

    return nullptr;
}


CControllerManager::CONTROLLER_LIST CControllerManager::GetList()
{
    return m_ControllerList;
}

/*
 *  コンストラクタ
 */
CControllerManager::CControllerManager(void)
{
}

/*
 *  コピーコンストラクタ
 */
CControllerManager::CControllerManager(const CControllerManager& rhs)
{
    (void)rhs;
}

/*
 *  デストラクタ
 */
CControllerManager::
~CControllerManager(void)
{
}

/*
 *  代入演算子
 */
CControllerManager& CControllerManager::operator=(const CControllerManager& rhs)
{
    (void)rhs;

    return *this;
}
