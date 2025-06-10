#include "data_manager.h"

const int CDataManager::m_max_game_num = 4;
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
    for (int i = 0; i < m_CurrentPlayerNum; i++)
    {
        m_PlayerWins[i] = 0;
    }
    m_MaxGameNum = m_max_game_num;
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
    for (int i = 0; i < m_CurrentPlayerNum; i++)
    {
        m_LastGameRanking[i] = UNIT_ID::NONE;
        m_PlayerWins[i] = 0;
    }
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
    if (num > 4 || num < 2) return;
    m_CurrentPlayerNum = num;

    ResetLastGameRanking();
}

GAME_ID CDataManager::GetSelectGameID()
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

void CDataManager::ResetLastGameRanking()
{
    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        m_LastGameRanking[i] = (UNIT_ID)((m_CurrentPlayerNum - 1) - i);
    }

    m_NowGameRankingNum = m_CurrentPlayerNum - 1;
}

void CDataManager::AddLastGameRanking(UNIT_ID unit_id)
{
    //引数が範囲外でないかのチェック
    if ((int)unit_id >= m_CurrentPlayerNum)
        return;


    //ランキングに被りがないかのチェック
    bool duplicate = false;

    for (int i = m_NowGameRankingNum + 1; i < m_CurrentPlayerNum; i++)
        if (m_LastGameRanking[i] == unit_id)
            duplicate = true;

    if (duplicate)
        return;


    //ランキングが既に埋まっていないかのチェック
    if (m_NowGameRankingNum < 0)
        return;


    //ランキングに追加
    m_LastGameRanking[m_NowGameRankingNum] = unit_id;
    m_NowGameRankingNum--;
}

UNIT_ID CDataManager::GetLastGameRanking(int num)
{
    //引数が適切でない場合
    if (num < 0 || (int)UNIT_ID::NONE <= num)
        return UNIT_ID::NONE;

    //引数に問題がない場合
    else
        return m_LastGameRanking[num];
}

int CDataManager::GetConnectControllerNum()
{
    return vivid::controller::GetConnectCount();
}

/*
 *  コンストラクタ
 */
CDataManager::
CDataManager(void)
    : m_PlayerWins()
    , m_CurrentPlayerNum(2)
    , m_LastGameRanking{UNIT_ID::NONE}
    , m_NowGameRankingNum(1)
{
    ResetLastGameRanking();
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
