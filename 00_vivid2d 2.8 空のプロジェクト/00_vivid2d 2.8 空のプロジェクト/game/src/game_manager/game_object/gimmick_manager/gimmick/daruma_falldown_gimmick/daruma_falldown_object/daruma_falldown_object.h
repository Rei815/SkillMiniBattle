#pragma once
#include "../../../../model_manager/model/model.h"

class CDaruma_FallDownObject
{
public:
    CDaruma_FallDownObject();
    ~CDaruma_FallDownObject();

    /*!
     *  @brief      ������
     *
     */
    void    Initialize(void);

    /*!
     *  @brief      �X�V
     */
    void    Update(void);

    /*!
     *  @brief      �`��
     */
    void    Draw(void);

    /*!
     *  @brief      ���
     */
    void    Finalize(void);

private:
    CModel			m_Model;
    CTransform		m_Transform;
    std::string     m_FileName;     //3D���f�����w�肷��t�@�C���p�X�̖��O�i��. data\\Models\\boss.mv1�j
};