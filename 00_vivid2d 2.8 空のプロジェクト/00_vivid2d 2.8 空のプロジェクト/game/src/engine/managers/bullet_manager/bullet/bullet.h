#pragma once

#include "../../launcher/launcher.h"
#include "collider_id.h"
#include "bullet_id.h"
#include "../../../../game/components/player_component/player_id.h"
#include "../../../core/game_object/game_object.h"
// �O���錾
class TransformComponent; // �L���b�V������|�C���^�̌^�Ȃ̂őO���錾���K�v
class IBullet : public  CGameObject
{
public:


    /*!
     *  @brief      �R���X�g���N�^
     */
    IBullet(COLLIDER_ID collider_id);

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
    virtual void    Initialize(FACTION_CATEGORY category, CShot::BulletParameters* bulletParams, const CVector3& position, const CVector3& direction);

    /*!
     *  @brief      ������
     *
     *  @param[in]  id              �e��ID
     *  @param[in]  position        �ʒu
     *  @param[in]  direction       ����
     */
    virtual void    Initialize(FACTION_CATEGORY category, const CVector3& position, const CVector3& direction);

    /*!
     *  @brief      �X�V
     */
    virtual void    Update(void);

    /*!
     *  @brief      �`��
     */
    virtual void    Draw(void);

    /*!
     *  @brief      �ʒu�擾
     *
     *  @return     �ʒu
     */
    CVector3        GetPosition(void);

    /*!
     *  @brief      ���x�x�N�g���擾
     *
     *  @return     ���x�x�N�g��
     */
    CVector3        GetVelocity(void);
    
    /*!
     *  @brief      ���x�x�N�g���̐ݒ�
     *
     *  @param[in]  velocity    ���x�x�N�g��
     */
    void            SetVelocity(const CVector3& velocity);

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
    void            Delete();

    /*!
     *  @brief      �������ʎq�擾
     *
     *  @return     ���ʎq
     */
    FACTION_CATEGORY GetBulletCategory(void);

    /*!
     *  @brief      �e�̔���ID�擾
     *
     *  @return     �e�̔���ID
     */
    COLLIDER_ID     GetColliderID(void);

    //CModel          GetModel(void);

    float           GetPower();

    BULLET_ID       GetID();

    /*!
     * @brief       ���a�擾
     * 
     * @return      ���a
     */
    float           GetRadius();

    /*!
     *  @brief      ���f���n���h���擾
     *
     *  @return     ���f���n���h��
     */
    int             GetModelHandle(void) const;

protected:

    std::shared_ptr<TransformComponent> m_TransformComponent;   //!< �L���b�V���p�R���|�[�l���g
    static const float                  m_life_time;            //!< ��������
    static const float                  m_radius;               //!< �e�̔��a(�����l)
    static const float	                m_max_speed;            //!< �ō����x
    static const DxLib::COLOR_F         m_color;                //!< �F

    CVector3                            m_Velocity;             //!< ���x
    CTimer                              m_LifeTimer;            //!< �������ԃ^�C�}�[
    float                               m_Power;                //!< �p���[
    float				                m_Speed;                //!< ����
    float				                m_Accleration;          //!< ������
    CVector3			                m_Direction;            //!< ���˂��ꂽ����
    BULLET_ID                           m_BulletID;             //!< �e�̎��
    COLLIDER_ID                         m_ColliderID;           //!< ����ID
    FACTION_CATEGORY                    m_Category;             //!< ����
	float							    m_Radius;               //!< ���a
};