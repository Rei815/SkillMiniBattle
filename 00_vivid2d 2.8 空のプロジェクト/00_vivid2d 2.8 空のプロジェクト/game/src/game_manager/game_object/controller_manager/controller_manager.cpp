#include "controller_manager.h"
#include "controller/keyboard/keyboard.h"
#include "controller/dummy_controller/dummy_controller.h"
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
    Create(CONTROLLER_ID::KEYBOARD);
    Create(CONTROLLER_ID::DUMMY);
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

        if (!controller->IsActive())
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

    switch (id)
    {
    case CONTROLLER_ID::ONE:
    case CONTROLLER_ID::TWO:
    case CONTROLLER_ID::THREE:
    case CONTROLLER_ID::FOUR:
        controller = new CController();
        break;
    case CONTROLLER_ID::KEYBOARD:
        controller = new CKeyboard();
        break;
    case CONTROLLER_ID::DUMMY:
        controller = new CDummyController();
        break;
    }
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

CController* CControllerManager::GetSpecifiedButtonUpController(BUTTON_ID button_id)
{
    if (m_ControllerList.empty()) return nullptr;

    CONTROLLER_LIST::iterator it = m_ControllerList.begin();

    while (it != m_ControllerList.end())
    {
        if ((*it)->GetButtonUp(button_id) == true)
            return (*it);

        ++it;
    }

    return nullptr;
}

CController* CControllerManager::GetSpecifiedButtonHoldController(BUTTON_ID button_id)
{
    if (m_ControllerList.empty()) return nullptr;

    CONTROLLER_LIST::iterator it = m_ControllerList.begin();

    while (it != m_ControllerList.end())
    {
        if ((*it)->GetButtonHold(button_id) == true)
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
