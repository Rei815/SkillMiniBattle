#include "data_manager.h"
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
    m_OverallRankingList->clear();

    m_MaxGameNum = 3;
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

    ResetLastGameRanking();
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
    //�������͈͊O�łȂ����̃`�F�b�N
    if ((int)unit_id >= m_CurrentPlayerNum)
        return;


    //�����L���O�ɔ�肪�Ȃ����̃`�F�b�N
    bool duplicate = false;

    for (int i = m_NowGameRankingNum + 1; i < m_CurrentPlayerNum; i++)
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

UNIT_ID CDataManager::GetLastGameRanking(int num)
{
    //�������K�؂łȂ��ꍇ
    if (num < 0 || (int)UNIT_ID::NONE <= num)
        return UNIT_ID::NONE;

    //�����ɖ�肪�Ȃ��ꍇ
    else
        return m_LastGameRanking[num];
}

/*
 *  �R���X�g���N�^
 */
CDataManager::
CDataManager(void)
    : m_PlayerWins()
    , m_CurrentPlayerNum(1)
    , m_LastGameRanking{UNIT_ID::NONE}
    , m_NowGameRankingNum(1)
{
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
