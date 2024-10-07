#pragma once
#include "../../model_manager/model/model.h"

class IObject
{
public:
    IObject();
    ~IObject();

    /*!
     *  @brief      ������
     *
     */
    virtual void    Initialize(const CVector3& pos);

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
    static const float  m_fall_speed;
    CModel			    m_Model;
    CTransform		    m_Transform;
    CVector3            m_Velocity;
    std::string         m_FileName;
    float               m_FallSpeed;
    bool                m_ActiveFlag;
};