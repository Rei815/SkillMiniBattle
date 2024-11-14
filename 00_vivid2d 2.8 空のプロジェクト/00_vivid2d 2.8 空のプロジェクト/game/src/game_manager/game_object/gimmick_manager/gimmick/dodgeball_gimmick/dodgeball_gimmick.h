#pragma once
#include "..\gimmick.h"
#include "..\..\..\launcher\launcher.h"
#include "..\..\..\effect_manager\effect\effect.h"

enum class CANNON_STATE
{
    SPAWN,
    MOVE,
    SHOT,
    STOP,
};

enum class CANNON_ROTATE
{
    RIGHT_GO,
    RIGHT_RETURN,
    LEFT_GO,
    LEFT_RETURN,
};

class CDodgeBallGimmick : public CGimmick
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     */
    CDodgeBallGimmick();

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CDodgeBallGimmick(void);

    /*!
     *  @brief      ������
     *
     */
    void    Initialize(IObject* object);

    void    Initialize(IObject* object, float time);

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

    CANNON_STATE    GetNowState();

    bool            GetShotFlag();

private:

    void Spawn();
    void Move();
    void Shot();
    void Stop();

    CTransform          m_SetTransform;
    CANNON_STATE        m_NowState;
    CANNON_ROTATE       m_NowRotate;
    CShot*              m_Shot;
    CTimer              m_MoveTimer;
    CTimer              m_ShotTimer;
    IEffect*            m_Effect;

    static const std::string    m_file_name;
    static const CVector3       m_spawn_pos;
    static const float          m_spawn_time;
    static const float          m_max_rotate_angle;
    static const float          m_rotate_time;
    static const float          m_min_rotate_time;
    static const float          m_shot_time;
    static const float	        m_effect_speed;    //!< �G�t�F�N�g�̕\���ʒu�̈ړ����x
};
