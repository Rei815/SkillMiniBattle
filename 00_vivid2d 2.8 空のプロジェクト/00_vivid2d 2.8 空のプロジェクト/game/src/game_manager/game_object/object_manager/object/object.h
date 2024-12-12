#pragma once
#include "../../model_manager/model/model.h"
#include "object_id.h"
#include "../../gimmick_manager/gimmick/gimmick.h"

class CGimmick;
class IObject
{
public:
    IObject();
    ~IObject();

    /*!
     *  @brief      ������
     *
     */
    virtual void    Initialize(OBJECT_ID id, const CTransform& pos);

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
     *  @brief      �I�u�W�F�N�gID�擾
     *
     *  @return     �I�u�W�F�N�gID
     */
    OBJECT_ID       GetObjectID(void);

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

    /*!
     *  @brief      �ʒu�擾
     *
     *  @return     �ʒu
     */
    CVector3        GetPosition();
    /*!
     *  @brief      �ʒu�ݒ�
     *
     *  @param[in]  position  �ʒu
     */
    void            SetPosition(const CVector3& position);

    /*!
     *  @brief      ��]�擾
     *
     *  @return     ��]
     */
    CVector3        GetRotation();

    /*!
     *  @brief      Tramsform�擾
     *
     *  @return     Tramsform
     */
    CTransform      GetTransform();

    /*!
     *  @brief      �ʒu�ݒ�
     *
     *  @param[in]  rotation  �ʒu
     */
    void            SetRotation(const CVector3& rotation);

    /*!
     *  @brief      ���x�ݒ�
     *
     *  @param[in]  velocity  ���x
     */
    void            SetVelocity(const CVector3& velocity);


    /*!
     *  @brief      ���f���擾
     *
     *  @return     ���f��
     */
    CModel          GetModel();

    void            SetGimmick(CGimmick* gimmick);
    
    CGimmick*       GetGimmick();

    /*!
     *  @brief      ���f���擾
     *
     *  @return     ���f��
     */
    std::string     GetTag();

    /*!
     *  @brief      �A���t�@�l�ݒ�
     *
     *  @param[in]  alpha  �A���t�@�l
     */
    void            SetAlpha(float alpha);

    /*!
     *  @brief      ����t���O�擾
     *
     *  @return     ����t���O
     */
    bool            GetColliderActiveFlag();

    /*!
     *  @brief      ����t���O�ݒ�
     *
     *  @param[in]  active  ����t���O
     */
    void            SetColliderActiveFlag(bool active);

protected:
    static const float  m_limit_alpha;
    OBJECT_ID           m_ObjectID;
    CModel			    m_Model;
    CTransform		    m_Transform;
    CVector3            m_Velocity;
    std::string         m_FileName;
    bool                m_ActiveFlag;
    float               m_Alpha;
    CGimmick*           m_Gimmick;
    std::string         m_Tag;

    bool                m_ColliderActiveFlag;
};