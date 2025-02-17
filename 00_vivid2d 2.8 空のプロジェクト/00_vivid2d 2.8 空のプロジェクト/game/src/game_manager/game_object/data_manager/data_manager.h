#pragma once

#include "vivid.h"
#include <list>
#include "../unit_manager/unit/player/player.h"
#include "../unit_manager/unit/unit_id.h"
#include "../scene_manager/scene/game/game_id.h"

class CDataManager
{
public:
    /*!
     *  @brief      �C���X�^���X�̎擾
     *
     *  @return     �C���X�^���X
     */
    static CDataManager& GetInstance(void);

    /*!
     *  @brief      ������
     */
    void            Initialize(void);

    /*!
     *  @brief      �X�V
     */
    void            Update(void);

    /*!
     *  @brief      ���
     */
    void            Finalize(void);

    /*!
     *  @brief      �v���C���[����������
     *
     *  @param[in]  unitID     ���j�b�gID
     */
    void            PlayerWin(UNIT_ID unitID);

    /*!
     *  @brief      �Q�����Ă���v���C���[�̐����擾
     *
     *  @return     �v���C���[�̐�
     */
    int             GetCurrentPlayer();

    /*!
     *  @brief      �Q�����Ă���v���C���[�̐���ݒ�
     *
     *  @param[in]  num     �v���C���[�̐�
     */
    void            SetCurrentPlayer(int num);

    /*!
     *  @brief      �Q�[����ID���擾
     *
     *  @return     �Q�[����ID
     */
    GAME_ID         GetSelectGameID();

    /*!
     *  @brief      �Q�[����ID��ݒ�
     *
     *  @param[in]  gameID     �Q�[����ID
     */
    void            SetGameID(GAME_ID gameID);

    /*!
     *  @brief      �v���C���[�̏������擾
     *
     *  @return     �v���C���[�̏�����
     */
    int             GetPlayerWin(int unitID);


    int             GetMaxGameNum();


    void            SetMaxGameNum(int num);


    void            ResetLastGameRanking();


    void            AddLastGameRanking(UNIT_ID unit_id);


    UNIT_ID         GetLastGameRanking(int num);

    /*!
     *  @brief      �R���g���[���[�̐ڑ������擾
     *
     *  @return     �R���g���[���[�̐ڑ���
     */
    int             GetConnectControllerNum();
private:

    /*!
     *  @brief      �R���X�g���N�^
     */
    CDataManager(void);

    /*!
     *  @brief      �R�s�[�R���X�g���N�^
     *
     *  @param[in]  rhs     �I�u�W�F�N�g
     */
    CDataManager(const CDataManager& rhs);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CDataManager(void);

    /*!
     *  @brief      ������Z�q
     *
     *  @param[in]  rhs ����I�u�W�F�N�g
     *
     *  @return     ���g�̃I�u�W�F�N�g
     */
    CDataManager& operator=(const CDataManager& rhs);

    /*!
     *  @brief      �v���C���[���X�g�^
     */
    using RANKING_LIST = std::vector<CPlayer*>;
    
    static const int    m_max_game_num;
    RANKING_LIST        m_OverallRankingList[(int)UNIT_ID::NONE];             //!< �S�̂̃����L���O���X�g

    UNIT_ID             m_LastGameRanking[(int)UNIT_ID::NONE];              //1�O�̃Q�[���̃����L���O
    int                 m_NowGameRankingNum;                                //1�O�̃Q�[���̃����L���O�����邽�߁A���̏��ʂ��i�[����ϐ�

    int                 m_PlayerWins[(int)UNIT_ID::NONE];
    int                 m_CurrentPlayerNum;

    GAME_ID             m_CurrentGameID;

    int                 m_MaxGameNum;
};