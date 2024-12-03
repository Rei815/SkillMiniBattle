#include "data_manager.h"
/*
 *  インスタンスの取得
 */
CDataManager&
CDataManager::
GetInstance(void)
{
    static CDataManager instance;

    return instance;
}

/*
 *  初期化
 */
void
CDataManager::
Initialize(void)
{
    m_OverallRankingList->clear();
}

/*
 *  更新
 */
void
CDataManager::Update(void)
{
}

/*
 *  解放
 */
void CDataManager::Finalize(void)
{
}

void CDataManager::PlayerWin(UNIT_ID unitID)
{
    if (0 > (int)unitID || (int)unitID > 4) return;

    ++m_PlayerWins[(int)unitID];
}

int CDataManager::GetCurrentPlayer()
{
    return m_CurrentPlayerNum;
}

void CDataManager::SetCurrentPlayer(int num)
{
    if (num > 4 || num < 1) return;
    m_CurrentPlayerNum = num;
}

GAME_ID CDataManager::GetGameID()
{
    return m_CurrentGameID;
}

void CDataManager::SetGameID(GAME_ID gameID)
{
    m_CurrentGameID = gameID;
}

int CDataManager::GetPlayerWin(int unitID)
{
    return m_PlayerWins[unitID];
}

int CDataManager::GetMaxGameNum()
{
    return m_MaxGameNum;
}

void CDataManager::SetMaxGameNum(int num)
{
    m_MaxGameNum = num;
}


/*
 *  コンストラクタ
 */
CDataManager::
CDataManager(void)
    : m_PlayerWins()
    , m_CurrentPlayerNum(1)
{
}

/*
 *  コピーコンストラクタ
 */
CDataManager::
CDataManager(const CDataManager& rhs)
{
    (void)rhs;
}

/*
 *  デストラクタ
 */
CDataManager::
~CDataManager(void)
{
}

/*
 *  代入演算子
 */
CDataManager&
CDataManager::
operator=(const CDataManager& rhs)
{
    (void)rhs;

    return *this;
}
