#pragma once
#include "../../model_manager/model/model.h"
#include "object_id.h"
#include "../../gimmick_manager/gimmick/gimmick.h"

enum class OBJECT_STATE
{
    WAIT,
    FALL,
    FALL_FINISH,
};
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
     *  @brief      ���x�ݒ�
     *
     *  @param[in]  velocity  ���x
     */
    void            SetVelocity(const CVector3& velocity);


    /*!
     *  @brief      ��Ԏ擾
     *
     *  @return     ���
     */
    OBJECT_STATE    GetState();

    /*!
     *  @brief      ���f���擾
     *
     *  @return     ���f��
     */
    CModel          GetModel();

    /*!
     *  @brief      ��Ԑݒ�
     *
     *  @param[in]  state   ���
     */
    void            SetState(OBJECT_STATE state);

    void            SetGimmick(CGimmick* gimmick);
    
    CGimmick*       GetGimmick();
protected:
    static const float  m_limit_alpha;
    OBJECT_ID           m_ObjectID;
    CModel			    m_Model;
    CTransform		    m_Transform;
    CVector3            m_Velocity;
    std::string         m_FileName;
    bool                m_ActiveFlag;
    float               m_Alpha;
    OBJECT_STATE        m_State;
    CGimmick*           m_Gimmick;

};