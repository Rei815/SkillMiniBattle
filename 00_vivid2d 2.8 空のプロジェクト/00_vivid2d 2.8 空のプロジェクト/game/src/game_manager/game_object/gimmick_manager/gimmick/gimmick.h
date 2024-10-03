
#pragma once
#include "gimmick_id.h"
#include "../../../../mathematics/mathematics.h"
#include "../../model_manager/model/model.h"

class CGimmick
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CGimmick();

    /*!
     *  @brief      �f�X�g���N�^
     */
    virtual ~CGimmick(void);

    /*!
     *  @brief      ������
     *
     */
    virtual void    Initialize();

    /*!
     *  @brief      �X�V
     */
    virtual void    Update(void);

    /*!
     *  @brief      �`��
     */
    virtual void    Draw(void);

    /*!
     *  @brief      ���
     */
    virtual void    Finalize(void);

    /*!
     *  @brief      �M�~�b�NID�擾
     *
     *  @return     �M�~�b�NID
     */
    GIMMICK_ID      GetGimmickID(void);

    /*!
     *  @brief      �A�N�e�B�u�t���O�擾
     *
     *  @return     �A�N�e�B�u�t���O
     */
    bool            GetActive(void);

    /*!
     *  @brief      �A�N�e�B�u�t���O�ݒ�
     *
     *  @param[in]  active  �A�N�e�B�u�t���O
     */
    void            SetActive(bool active);

protected:
    CTransform	            m_Transform;    //!< �g�����X�t�H�[��
    bool                    m_ActiveFlag;       //!< �A�N�e�B�u�t���O
};
