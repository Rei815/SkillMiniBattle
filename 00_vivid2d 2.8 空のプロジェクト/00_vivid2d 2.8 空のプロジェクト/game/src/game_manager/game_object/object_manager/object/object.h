#pragma once
#include "../../model/model.h"
#include "object_id.h"
#include "../../gimmick_manager/gimmick/gimmick.h"
#include <memory>
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
    bool            IsActive(void);

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
     *  @brief      �X�P�[���ݒ�
     *
     *  @param[in]  scale  �I�u�W�F�N�g�̑傫��
     */
    void            SetScale(float scale);

    /*!
     *  @brief      �X�P�[���ݒ�
     *
     *  @param[in]  scale  �I�u�W�F�N�g�̑傫��
     */
    void            SetScale(const CVector3& scale);


    /*!
     *  @brief      ���f���擾
     *
     *  @return     ���f��
     */
    CModel          GetModel();

    void            SetGimmick(std::shared_ptr<CGimmick> gimmick);
    
    std::shared_ptr<CGimmick>       GetGimmick();

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
    static const float          m_limit_alpha;          //!< �A���t�@�l�̌��E�l
    OBJECT_ID                   m_ObjectID;             //!< �I�u�W�F�N�g��ID
    CModel			            m_Model;                //!< ���f��
    CTransform		            m_Transform;            //!< �g�����X�t�H�[��
    CVector3                    m_Velocity;             //!< ���x
    std::string                 m_FileName;             //!< �t�@�C����
    bool                        m_ActiveFlag;           //!< �A�N�e�B�u�t���O
    float                       m_Alpha;                //!< �A���t�@�l
    std::shared_ptr<CGimmick>   m_Gimmick;              //!< �M�~�b�N
    std::string                 m_Tag;                  //!< �^�O��
    bool                        m_ColliderActiveFlag;   //!< �������邩
};