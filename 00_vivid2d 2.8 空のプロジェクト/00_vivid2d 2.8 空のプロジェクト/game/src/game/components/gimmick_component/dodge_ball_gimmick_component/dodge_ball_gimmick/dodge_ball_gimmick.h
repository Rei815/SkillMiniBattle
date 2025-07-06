#pragma once
#include <memory>
#include "../../../../../engine/core/game_object/game_object.h"
#include "../../../../../engine/managers/effect_manager/effect/effect.h"
#include "../../../../../engine/managers/launcher/shot/shot.h"

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

class CDodgeBallGimmick
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
    void    Initialize(CGameObject* object);

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

    bool            GetOperatingFlag();

    void            SetOperationFlag(bool flag);
private:

    void Spawn();
    void Move();
    void Shot();
    void Stop();

    static const CVector3           m_spawn_pos;
    static const float              m_spawn_time;
    static const float              m_max_rotate_angle;
    static const float              m_rotate_time;
    static const float              m_min_rotate_time;
    static const float              m_shot_time;
    static const float	            m_effect_speed;    //!< �G�t�F�N�g�̕\���ʒu�̈ړ����x
    CTransform                      m_SetTransform;
    CANNON_STATE                    m_NowState;
    CANNON_ROTATE                   m_NowRotate;
    std::shared_ptr<CShot>          m_Shot;
    CTimer                          m_Timer;
    CTimer                          m_MoveTimer;
    CTimer                          m_ShotTimer;
    std::shared_ptr<IEffect>        m_Effect;
    CGameObject*                    m_Object;
    bool                            m_OperationFlag;
};
