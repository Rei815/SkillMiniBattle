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
 *  �R���X�g���N�^
 */
CDataManager::
CDataManager(void)
    : m_PlayerWins()
    , m_CurrentPlayerNum(1)
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
