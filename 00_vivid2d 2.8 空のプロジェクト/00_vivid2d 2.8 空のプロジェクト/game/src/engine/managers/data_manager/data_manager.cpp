#include "data_manager.h"

const int CDataManager::m_max_game_num = 4;
const int CDataManager::m_required_wins = 3;
const int CDataManager::m_min_player_join = 2;
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
    for (int i = 0; i < m_CurrentJoinPlayerNum; i++)
        m_PlayerWins[i] = 0;
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
    for (int i = 0; i < m_CurrentJoinPlayerNum; i++)
    {
        m_LastGameRanking[i] = PLAYER_ID::NONE;
        m_PlayerWins[i] = 0;
    }
}

void CDataManager::PlayerWin(PLAYER_ID unitID)
{
    if (0 > (int)unitID || (int)unitID > 4) return;

    ++m_PlayerWins[(int)unitID];
}

int CDataManager::GetCurrentJoinPlayer()
{
    return m_CurrentJoinPlayerNum;
}

void CDataManager::SetCurrentJoinPlayer(int num)
{
    if (num > m_max_player_join || num < m_min_player_join) return;
    m_CurrentJoinPlayerNum = num;

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
    return m_max_game_num;
}

int CDataManager::GetRequiredWins()
{
    return m_required_wins;
}

int CDataManager::GetMaxJoinPlayerNum()
{
    return m_max_player_join;
}

int CDataManager::GetActiveControllerNum()
{
    return m_active_controller_num;
}

void CDataManager::ResetLastGameRanking()
{
    for (int i = 0; i < (int)PLAYER_ID::NONE; i++)
    {
        m_LastGameRanking[i] = (PLAYER_ID)((m_CurrentJoinPlayerNum - 1) - i);
    }

    m_NowGameRankingNum = m_CurrentJoinPlayerNum - 1;
}

void CDataManager::AddLastGameRanking(PLAYER_ID unit_id)
{
    //引数が範囲外でないかのチェック
    if ((int)unit_id >= m_CurrentJoinPlayerNum)
        return;


    //ランキングに被りがないかのチェック
    bool duplicate = false;

    for (int i = m_NowGameRankingNum + 1; i < m_CurrentJoinPlayerNum; i++)
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

PLAYER_ID CDataManager::GetLastGameRanking(int num)
{
    //引数が適切でない場合
    if (num < 0 || (int)PLAYER_ID::NONE <= num)
        return PLAYER_ID::NONE;

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
    , m_CurrentJoinPlayerNum(m_min_player_join)
    , m_LastGameRanking{ PLAYER_ID::NONE}
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
