#include "controller_manager.h"

/*
 *  �C���X�^���X�̎擾
 */
CControllerManager& CControllerManager::GetInstance(void)
{
    static CControllerManager instance;

    return instance;
}

/*
 *  ������
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
 *  �X�V
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
 *  ���
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


/*
 *  �R���X�g���N�^
 */
CControllerManager::CControllerManager(void)
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
CControllerManager::CControllerManager(const CControllerManager& rhs)
{
    (void)rhs;
}

/*
 *  �f�X�g���N�^
 */
CControllerManager::
~CControllerManager(void)
{
}

/*
 *  ������Z�q
 */
CControllerManager& CControllerManager::operator=(const CControllerManager& rhs)
{
    (void)rhs;

    return *this;
}
