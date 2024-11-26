#pragma once

#include "vivid.h"
#include <list>
#include "../unit_manager/unit/player/player.h"
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
    void        Initialize(void);

    /*!
     *  @brief      �X�V
     */
    void        Update(void);

    /*!
     *  @brief      ���
     */
    void        Finalize(void);

    void        PlayerWin(UNIT_ID unitID);

    int         GetCurrentPlayer();

    void        SetCurrentPlayer(int num);

    GAME_ID     GetGameID();

    void        SetGameID(GAME_ID gameID);


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
    
    RANKING_LIST        m_OverallRankingList[4];             //!< �S�̂̃����L���O���X�g

    int                 m_PlayerWins[4];
    int                 m_CurrentPlayerNum;

    GAME_ID             m_CurrentGameID;
};