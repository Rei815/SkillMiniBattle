#pragma once

#include "vivid.h"
#include <list>
#include "gimmick/gimmick.h"
class CGimmickManager
{
public:
    /*!
     *  @brief      �C���X�^���X�̎擾
     *
     *  @return     �C���X�^���X
     */
    static CGimmickManager& GetInstance(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(void);

    /*!
     *  @brief      �X�V
     */
    void        Update(void);

    /*!
     *  @brief      �`��
     */
    void        Draw(void);

    /*!
     *  @brief      ���
     */
    void        Finalize(void);

    /*!
     *  @brief      �M�~�b�N����
     *
     *  @param[in]  id              �M�~�b�N��ID
     */
    void        Create(GIMMICK_ID id);

private:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CGimmickManager(void);

    /*!
     *  @brief      �R�s�[�R���X�g���N�^
     *
     *  @param[in]  rhs     �I�u�W�F�N�g
     */
    CGimmickManager(const CGimmickManager& rhs);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CGimmickManager(void);

    /*!
     *  @brief      ������Z�q
     *
     *  @param[in]  rhs ����I�u�W�F�N�g
     *
     *  @return     ���g�̃I�u�W�F�N�g
     */
    CGimmickManager& operator=(const CGimmickManager& rhs);

    /*!
     *  @brief      �M�~�b�N���X�g�^
     */
    using GIMMICK_LIST = std::list<CGimmick*>;

    GIMMICK_LIST             m_GimmickList;             //!< �M�~�b�N���X�g
};