#pragma once

#include "../../../../mathematics\mathematics.h"
#include "../../model_manager/model/model.h"
#include "../../../../collider/sphere_collider/sphere_collider.h"
#include "../../launcher/launcher.h"
#include "collider_id.h"
class IBullet
{
public:


    /*!
     *  @brief      �R���X�g���N�^
     */
    IBullet(const std::string& file_name, COLLIDER_ID collider_id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    virtual ~IBullet(void);

    /*!
     *  @brief      ������
     *
     *  @param[in]  category        ���j�b�g���ʎq
     *  @param[in]  position        �ʒu
     *  @param[in]  direction       ����
     */
    virtual void    Initialize(UNIT_CATEGORY category, CShot::BulletParameters* bulletParameter, const CVector3& position, const CVector3& direction);

    /*!
     *  @brief      ������
     *
     *  @param[in]  category        ���j�b�g���ʎq
     *  @param[in]  id              �e��ID
     *  @param[in]  position        �ʒu
     *  @param[in]  direction       ����
     */
    virtual void    Initialize(UNIT_CATEGORY category, const CVector3& position, const CVector3& direction);

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
     *  @brief      �ʒu�擾
     *
     *  @return     �ʒu
     */
    CVector3        GetPosition(void);

    /*!
     *  @brief      �ʒu�ݒ�
     *
     *  @param[in]  position    �ʒu
     */
    void            SetPosition(const CVector3& position);

    /*!
     *  @brief      ���x�x�N�g���擾
     *
     *  @return     ���x�x�N�g��
     */
    CVector3        GetVelocity(void);

    /*!
     *  @brief      ���a�擾
     *
     *  @return     ���a
     */
    float           GetRadius();

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
     *  @brief      ���j�b�g���ʎq�擾
     *
     *  @return     ���j�b�g���ʎq
     */
    UNIT_CATEGORY   GetBulletCategory(void);

    /*!
     *  @brief      �e�̐F�擾
     *
     *  @return     �e�̐F
     */
    unsigned int    GetBulletColor(void);

    /*!
     *  @brief      �e�̃_���[�W�擾
     *
     *  @return     �e�̃_���[�W
     */
    float           GetBulletDamage(void);


    /*!
     *  @brief      �e�̔���ID�擾
     *
     *  @return     �e�̔���ID
     */
    COLLIDER_ID     GetColliderID(void);

    /*!
     *  @brief      �e�̔���ID�擾
     *
     *  @return     �e�̔���ID
     */
    CVector3        GetColliderPosA(void);
    /*!
     *  @brief      �e�̔���ID�擾
     *
     *  @return     �e�̔���ID
     */
    CVector3        GetColliderPosB(void);

    CModel          GetModel(void);

    float           GetPower();
protected:


    static const unsigned int   m_player_color;     //!< �v���C���[�̒e�̐F
    static const unsigned int   m_enemy_color;      //!< �G�̒e�̐F
    static const int            m_life_time;        //!< ��������
    static const float          m_radius;           //!< �e�̔��a(�����l)
    static const std::string    m_file_name;        //!< �ǂݍ��ރt�@�C����
    static const float	        m_max_speed;        //!< �ō����x

    CModel                      m_Model;            //!< ���f��
    std::string                 m_FileName;         //!< ���f���̃t�@�C����
    CTransform                  m_Transform;        //!< �ʒu
    CVector3                    m_Velocity;         //!< ���x
    float                       m_Radius;
    unsigned int                m_Color;            //!< �F
    float                       m_Rotation;         //!< ��]�l
    bool                        m_ActiveFlag;       //!< �A�N�e�B�u�t���O
    UNIT_CATEGORY               m_Category;         //!< �e���ʎq
    int                         m_LifeTimer;        //!< �������ԃ^�C�}�[
    float                       m_Damage;           //!< �_���[�W
    float                       m_Power;            //!< �p���[
    float				        m_Speed;            //!< ����
    float				        m_Accleration;		//!< ������
    CVector3			        m_Direction;

    COLLIDER_ID                 m_ColliderID;       //!< ����ID
    CVector3                    m_CapsulePosA;      //!< �J�v�Z�����`�������_���̈�_
    CVector3                    m_CapsulePosB;      //!< �J�v�Z�����`�������_���̈�_
};