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
}

/*
 *  �X�V
 */
void
CControllerManager::Update(void)
{
    m_ControllerNum = vivid::controller::GetConnectCount();

    //vivid::DrawText(30,std::to_string(m_ControllerNum), vivid::Vector2(0, 0));

    //m_ControllerIDList.
}



/*
 *  ���
 */
void
CControllerManager::Finalize(void)
{
}

void CControllerManager::SetControllerNum(int num)
{
    m_ControllerNum = num;
}

bool CControllerManager::GetControllerNum()
{
    return m_ControllerNum;
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
