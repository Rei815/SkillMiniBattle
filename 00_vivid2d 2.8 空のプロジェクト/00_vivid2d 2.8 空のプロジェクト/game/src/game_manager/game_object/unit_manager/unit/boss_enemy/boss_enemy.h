#pragma once

#include "..\..\..\..\..\mathematics\mathematics.h"
#include "..\unit.h"
#include "../../../model_manager/model/model.h"
#include "../../../bullet_manager/bullet/bullet.h"
#include "../../../launcher/launcher.h"

class CBossEnemy : public IUnit
{
public:

    CBossEnemy();

    ~CBossEnemy();

    /*!
     *  @brief      ������
     *
     *  @param[in]  position    �ʒu
     *  @param[in]  moveID      ������ID
     *  @param[in]  aimFlag     �_�����ǂ���
     */
    virtual void    Initialize(const CVector3& position, MOVE_ID moveID, bool aimFlag);

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

    enum BURST_STATE
    {
        WAIT,
        FIRE,
    };

    /*!
     *  @brief      �U��
     */
    void        Attack(void);

    void        _Attack(void);

    /*!
     *  @brief      �ړ�
     */
    void        Move(void);

    /*!
     *  @brief      ���S
     */
    void        Dead(void);

    /*!
     *  @brief      �U���p�^�[��A
     */
    void    Appear(void);

    /*!
     *  @brief      �ҋ@
     */
    void    Wait(void);

    /*!
     *  @brief      �U���p�^�[��A
     */
    void    MoveAttack(void);

    /*!
     *  @brief      �U���p�^�[��B
     */
    void    StayAttack(void);

    /*!
     *  @brief      �U���p�^�[��C
     */
    void    FallAttack(void);


    /*!
     *  @brief      �U���p�^�[��ID
     */
    enum class ATTACK_PATTERN
    {
        WAIT,
        MOVE_ATTACK,
        STAY_ATTACK,
        FALL_ATTACK,
    };

    static const float              m_max_life;                 //!< �ő僉�C�t
    static const float              m_move_speed;               //!< �ړ����x
    static const float              m_radius;                   //!< ���a
    static const float              m_attack_time;              //!< �ړ�����
    static const float              m_fall_accelerator;         //!< �������x
    static const int                m_wait_time;                //!< �ҋ@����
    //static const float              m_jump_power;             //!< �W�����v��
    //static const float              m_fall_accelerator;       //!< ���������x

    static const CVector3           m_scale;                    //!< �傫��
    CVector3                        m_Accelerator;              //!< �����x
    ATTACK_PATTERN                  m_AttackPattern;            //!< �U���p�^�[��
    CVector3                        m_StartPosition;            //!< �����ʒu
    CVector3                        m_WaitPosition;             //!< �ҋ@�ʒu
    float                           m_AttackTimer;              //!< �ړ��^�C�}�[
    int                             m_WaitTimer;                //!< �ҋ@�^�C�}�[
    float                           m_FallSpeed;                //!< �������x
    CVector3                        m_ShockWavePos;
    CShot*                          m_ShotShockWave1;
    CShot*                          m_ShotShockWave2;
    CShot*                          m_ShotShockWave3;
    CShot*                          m_ShotHomingDelayShotgun;
    CShot*                          m_ShotHomingShotgun;
    CShot*                          m_ShotShotgun;
    bool                            m_BossLife;

};