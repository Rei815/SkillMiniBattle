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
}

/*
 *  更新
 */
void
CControllerManager::Update(void)
{
    m_ControllerNum = vivid::controller::GetConnectCount();

    //vivid::DrawText(30,std::to_string(m_ControllerNum), vivid::Vector2(0, 0));

    //m_ControllerIDList.
}



/*
 *  解放
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
