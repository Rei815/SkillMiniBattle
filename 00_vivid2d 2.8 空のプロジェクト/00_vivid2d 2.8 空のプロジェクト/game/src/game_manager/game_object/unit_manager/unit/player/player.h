#pragma once

#include "..\..\..\..\..\mathematics\mathematics.h"
#include "..\unit.h"
#include "../../../model_manager/model/model.h"
#include "../../../bullet_manager/bullet/bullet.h"
#include "../../../skill_manager/skill/skill.h"

class CSkill;

class CPlayer: public IUnit
{
public:

	CPlayer();

	~CPlayer();

    /*!
     *  @brief      ������
     *
     *  @param[in]  position    �����ʒu
     */
    virtual void        Initialize(UNIT_ID unit_id, const CVector3& position, const std::string& file_name, vivid::controller::DEVICE_ID controller);

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
     *  @brief      �s���̉s��ݒ�
     *
     *  @param[in]  flag    �s���t���O
 */
    void        SetActionFlag(bool flag);

    vivid::controller::DEVICE_ID GetController(void);
    
    /*!
     *  @brief      �X�L���̎擾
     *
     *  @return     �X�L��
     */
    CSkill*         GetSkill();

    /*!
     *  @brief      �X�L���̃Z�b�g
     *
     *  @param[in]  skill    �X�L���̃|�C���^
     */
    void        SetSkill(CSkill* skill);

    /*!
     *  @brief      �X�L�����ɂ��X�s�[�h�{���̃Z�b�g
     *
     *  @param[in]  rate    �{��
     */
    void        SetMoveSpeedRate(float rate = 1.0f);

    /*!
     *  @brief      �X�L�����ɂ��X�s�[�h�{���̏�Z
     *  @param[in]  rate    �{��
     */
    void        MulMoveSpeedRate(float rate = 1.0f);

    /*!
     *  @brief      �X�L�����ɂ��X�s�[�h�{���̏��Z
     *  @param[in]  rate    �{��
     */
    void        DivMoveSpeedRate(float rate = 1.0f);

    /*!
     *  @brief      �X�L�����ɂ��W�����v�{���̃Z�b�g
     *
     *  @param[in]  rate    �{��
     */
    void        SetJumpPowerRate(float rate = 1.0f);

    /*!
     *  @brief      �X�L�����ɂ��W�����v�{���̏�Z
     *
     *  @param[in]  rate    �{��
     */
    void        MulJumpPowerRate(float rate = 1.0f);

    /*!
     *  @brief      �X�L�����ɂ��W�����v�{���̏��Z
     *
     *  @param[in]  rate    �{��
     */
    void        DivJumpPowerRate(float rate = 1.0f);

    /*!
     *  @brief      ���G���ʂ̕t�^
     *
     *  @param[in]  invincible_time    ���G����
     */
    void        StartInvincible(float invincible_time);

    bool        GetPlayerMoving();

    CVector3    GetForwardVector();
protected:
    /*!
     *  @brief      �U��
     */
    void        Attack(void);

    /*!
     *  @brief      ��e
     *  @param[in]  bullet          ��e�����e
     *  @param[in]  hit_position    ��e�ʒu
     */
    void    HitBullet(IBullet* bullet, CVector3 hit_position);

    /*!
     *  @brief      �Ռ���^����
     *  @param[in]  hit_position   �Ռ��̈ʒu
     *  @param[in]  direction      ����
     *  @param[in]  float          �Ռ���
     */
    void    Impact(const CVector3& hit_position, const CVector3& direction, float power);
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
    static const float              m_height;                       //!< ����
    static const float              m_move_speed;                   //!< �ړ����x
    static const float              m_jump_power;                   //!< �W�����v��
    static const float              m_move_friction;                //!< �ړ��p������
    static const float              m_fly_away_speed;               //!< ��e���̐�����ё��x
    static const float              m_max_life;                     //!< �ő僉�C�t
    static const float              m_max_invincible_time;          //!< ���G����
    static const int                m_invincible_visible_interval;  //!< ���G���Ԓ��̓_�ŊԊu
    static const float              m_fall_accelerator;             //!< ���������x

    float                           m_MoveSpeedRate;                //!< �ړ����x�̔{��
    float                           m_JumpPowerRate;                //!< �W�����v�͂̔{��

    CSkill*                         m_Skill;                        //!< �X�L��

    float                           m_FallSpeed;                    //!< �������x
    CVector3                        m_Accelerator;                  //!< �����x
    CVector3                        m_InitialPosition;              //!< �����ʒu
    bool                            m_StopFlag;                     //!< ��~�t���O
    bool                            m_FrictionFlag;                 //!< �����t���O
    CTimer                          m_InvincibleTimer;              //!< ���G���ԃ^�C�}�[
    bool                            m_ActionFlag;                   //!< �s�������L���t���O
    DxLib::COLOR_F                  m_Color;
    vivid::controller::DEVICE_ID    m_Controller;                   //!< �R���g���[���[����
    CVector3                        m_ForwardVector;                //!< ���ʕ����̃x�N�g��
};