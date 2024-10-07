#pragma once

#include "..\..\..\..\..\mathematics\mathematics.h"
#include "..\unit.h"
#include "../../../model_manager/model/model.h"
#include "../../../bullet_manager/bullet/bullet.h"

class CPlayer: public IUnit
{
public:

	CPlayer(UNIT_ID unit_id);

	~CPlayer();

    /*!
     *  @brief      ������
     *
     *  @param[in]  position    �����ʒu
     */
    virtual void        Initialize(const CVector3& position, MOVE_ID moveId);

    /*!
     *  @brief      �X�V
     */
    virtual void        Update(void);

    /*!
     *  @brief      �`��
     */
    virtual void        Draw(void);

    /*!
     *  @brief      ���
     */
    virtual void        Finalize(void);

    /*!
     *  @brief      ���C�t�擾
     *
     *  @return     ���݂̃��C�t
     */
    float        GetLife(void);


/*!
     *  @brief      �s���\���ǂ�����ݒ�
     *
     *  @param[in]  flag    �s���\���ǂ���
 */
    void        SetActionFlag(bool flag);

protected:
    /*!
     *  @brief      �U��
     */
    void        Attack(void);

    /*!
     *  @brief      ���S
     */
    void        Defeat(void);


    /*!
     *  @brief      ����
     */
    void        Control(void);

    /*!
     *  @brief      �ړ�����
     */
    void        Move(void);

    /*!
     *  @brief      �_���[�W�����������̏���(�_���[�W�̌v�Z��Unit)
     */
    void        Damage(void);

    static const float              m_radius;                       //!< ���a
    static const float              m_move_speed;                   //!< �ړ����x
    static const float              m_jump_power;                   //!< �W�����v��
    static const float              m_move_friction;                //!< �ړ��p������
    static const float              m_max_life;                     //!< �ő僉�C�t
    static const int                m_max_invincible_time;          //!< ���G����
    static const int                m_invincible_visible_interval;  //!< ���G���Ԓ��̓_�ŊԊu
    static const float              m_fall_accelerator;             //!< ���������x
    static const std::string        m_file_name;                    //!< �ǂݍ��ރt�@�C����

    CVector3                        m_Offset;                       //!< �J�����Ƃ̋���
    float                           m_FallSpeed;                    //!< �������x
    CVector3                        m_Accelerator;                  //!< �����x
    bool                            m_IsGround;                     //!< �n��ɂ��邩
    bool                            m_StopFlag;                     //!< ��~�t���O
    int                             m_InvincibleTime;               //!< ���G����
    bool                            m_ActionFlag;                   //!< �s�������L���t���O
    DxLib::COLOR_F                  m_Color;
    int                             m_Controller;                   //!< �R���g���[���[����
    int                             m_WinsNum;                      //!< ��������
};