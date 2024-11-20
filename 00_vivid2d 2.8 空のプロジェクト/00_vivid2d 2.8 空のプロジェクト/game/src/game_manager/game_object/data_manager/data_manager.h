#pragma once

#include "vivid.h"
#include <list>
#include "../unit_manager/unit/player/player.h"

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
    using RANKING_LIST = std::list<CPlayer*>;

    RANKING_LIST           m_OverallRankingList;             //!< �S�̂̃����L���O���X�g

};