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
    int             GetCurrentJoinPlayer();

    /*!
     *  @brief      �Q�����Ă���v���C���[�̐���ݒ�
     *
     *  @param[in]  num     �v���C���[�̐�
     */
    void            SetCurrentJoinPlayer(int num);

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
     *  @param[in]  unitID     ���j�b�g��ID
     * 
     *  @return     �v���C���[�̏�����
     */
    int             GetPlayerWin(int unitID);

    /*!
     *  @brief      �~�j�Q�[���̐����擾
     *
     *  @return     �~�j�Q�[���̐�
     */
    int             GetMaxGameNum();

    /*!
     *  @brief      �K�v�ȏ��������擾
     *
     *  @return     �K�v�ȏ�����
     */
    int             GetRequiredWins();

    /*!
     *  @brief      �ő�̎Q���\�ȃv���C���[�̐����擾
     *
     *  @return     �ő�̎Q���\�ȃv���C���[�̐����擾
     */
    int             GetMaxJoinPlayerNum();

    /*!
     *  @brief      ����\�ȃR���g���[���[�����擾
     *
     *  @return     ����\�ȃR���g���[���[��
     */
    int             GetActiveControllerNum();

    /*!
     *  @brief      �O��̃~�j�Q�[���̃����L���O�����Z�b�g
     */
    void            ResetLastGameRanking();

    /*!
     *  @brief      �O��̃~�j�Q�[���̃����L���O�Ƀv���C���[��ǉ�
     */
    void            AddLastGameRanking(UNIT_ID unit_id);

    /*!
     *  @brief      �O��̃~�j�Q�[���̃����L���O���擾
     * 
     *  @param[in]  num     ���j�b�g��ID
     *  @return     ���j�b�g��ID
     */
    UNIT_ID         GetLastGameRanking(int num);

    /*!
     *  @brief      �R���g���[���[�̐ڑ������擾
     *
     *  @return     �R���g���[���[�̐ڑ���
     */
    int             GetConnectControllerNum();

    static const int    m_max_player_join = 4;                      //!< �Q���\�ȍő�l��
    static const int    m_active_controller_num = 5;                //!< ����\�ȃR���g���[���[��

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

    static const int    m_max_game_num;                         //!< �ő�̃Q�[����
    static const int    m_required_wins;                        //!< �K�v�ȏ�����
    static const int    m_min_player_join;                      //!< �Q�[���ɕK�v�ȍŏ��̐l��

    UNIT_ID             m_LastGameRanking[(int)UNIT_ID::NONE];  //!< 1�O�̃Q�[���̃����L���O
    int                 m_NowGameRankingNum;                    //!< 1�O�̃Q�[���̃����L���O�����邽�߁A���̏��ʂ��i�[����ϐ�
    int                 m_PlayerWins[(int)UNIT_ID::NONE];       //!< �v���C���[�̏�����
    int                 m_CurrentJoinPlayerNum;                 //!< ���݂̎Q�����Ă���v���C���[
    GAME_ID             m_CurrentGameID;                        //!< ���ݑI�΂�Ă���Q�[����ID

};