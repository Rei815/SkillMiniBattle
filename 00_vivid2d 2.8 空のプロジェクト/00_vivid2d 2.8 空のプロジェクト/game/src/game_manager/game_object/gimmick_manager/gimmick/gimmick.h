
#pragma once
#include "gimmick_id.h"
#include "../../../../mathematics/mathematics.h"
#include "../../model_manager/model/model.h"

class IGimmick
{
public:
    IGimmick();
    /*!
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  gimmick_id     �M�~�b�NID
     */
    IGimmick(GIMMICK_ID gimmick_id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    virtual ~IGimmick(void);

    /*!
     *  @brief      ������
     *
     */
    virtual void    Initialize(const CVector3& position);

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
    GIMMICK_ID         GetGimmickID(void);

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

    CModel                  m_Model;
    CTransform	            m_Transform;		    //!< �g�����X�t�H�[��

};
