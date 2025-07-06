#include "data_manager.h"

const int CDataManager::m_max_game_num = 4;
const int CDataManager::m_required_wins = 3;
const int CDataManager::m_min_player_join = 2;
/*
 *  �C���X�^���X�̎擾
 */
CDataManager&
CDataManager::
GetInstance(void)
{
    static CDataManager instance;

    return instance;
}

/*
 *  ������
 */
void
CDataManager::
Initialize(void)
{
    for (int i = 0; i < m_CurrentJoinPlayerNum; i++)
        m_PlayerWins[i] = 0;
}

/*
 *  �X�V
 */
void
CDataManager::Update(void)
{
}

/*
 *  ���
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
    //�������͈͊O�łȂ����̃`�F�b�N
    if ((int)unit_id >= m_CurrentJoinPlayerNum)
        return;


    //�����L���O�ɔ�肪�Ȃ����̃`�F�b�N
    bool duplicate = false;

    for (int i = m_NowGameRankingNum + 1; i < m_CurrentJoinPlayerNum; i++)
        if (m_LastGameRanking[i] == unit_id)
            duplicate = true;

    if (duplicate)
        return;


    //�����L���O�����ɖ��܂��Ă��Ȃ����̃`�F�b�N
    if (m_NowGameRankingNum < 0)
        return;


    //�����L���O�ɒǉ�
    m_LastGameRanking[m_NowGameRankingNum] = unit_id;
    m_NowGameRankingNum--;
}

PLAYER_ID CDataManager::GetLastGameRanking(int num)
{
    //�������K�؂łȂ��ꍇ
    if (num < 0 || (int)PLAYER_ID::NONE <= num)
        return PLAYER_ID::NONE;

    //�����ɖ�肪�Ȃ��ꍇ
    else
        return m_LastGameRanking[num];
}

int CDataManager::GetConnectControllerNum()
{
    return vivid::controller::GetConnectCount();
}

/*
 *  �R���X�g���N�^
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
 *  �R�s�[�R���X�g���N�^
 */
CDataManager::
CDataManager(const CDataManager& rhs)
{
    (void)rhs;
}

/*
 *  �f�X�g���N�^
 */
CDataManager::
~CDataManager(void)
{
}

/*
 *  ������Z�q
 */
CDataManager&
CDataManager::
operator=(const CDataManager& rhs)
{
    (void)rhs;

    return *this;
}
