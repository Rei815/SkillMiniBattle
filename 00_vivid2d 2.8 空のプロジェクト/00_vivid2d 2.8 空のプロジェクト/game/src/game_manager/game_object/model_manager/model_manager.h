#pragma once

#include "vivid.h"
#include "..\..\..\utility\utility.h"
#include <list>
#include "model/model.h"

class CModelManager
{
public:
    /*!
     *  @brief      �C���X�^���X�̎擾
     *
     *  @return     �C���X�^���X
     */
    static CModelManager& GetInstance(void);

    /*!
     *  @brief      �ǂݍ���
     */
    void        Load(void);

    /*!
     *  @brief      �폜
     */
    void        UnLoad(void);

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

private:

    /*!
     *  @brief      �R���X�g���N�^
     */
    CModelManager(void);

    /*!
     *  @brief      �R�s�[�R���X�g���N�^
     *
     *  @param[in]  rhs     �I�u�W�F�N�g
     */
    CModelManager(const CModelManager& rhs);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CModelManager(void);

    /*!
     *  @brief      ������Z�q
     *
     *  @param[in]  rhs ����I�u�W�F�N�g
     *
     *  @return     ���g�̃I�u�W�F�N�g
     */
    CModelManager& operator=(const CModelManager& rhs);

    /*!
     *  @brief      ���f�����X�g�^
     */
    using MODEL_LIST = std::list<CModel*>;

    MODEL_LIST              m_ModelList;                                //!< ���f�����X�g

    static const char*      m_model_file_names[(int)MODEL_ID::MAX];     //!< ���f���̃t�@�C����

    int                     m_model_handles[(int)MODEL_ID::MAX];        //!< ���f���̃t�@�C����

    int                     m_Handle;                                   //!< �n���h��
};
