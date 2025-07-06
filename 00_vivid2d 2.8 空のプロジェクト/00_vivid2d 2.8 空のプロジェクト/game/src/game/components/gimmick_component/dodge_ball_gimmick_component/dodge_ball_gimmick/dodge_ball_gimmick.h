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
     *  @brief      コンストラクタ
     *
     */
    CDodgeBallGimmick();

    /*!
     *  @brief      デストラクタ
     */
    ~CDodgeBallGimmick(void);

    /*!
     *  @brief      初期化
     *
     */
    void    Initialize(CGameObject* object);

    /*!
     *  @brief      更新
     */
    void    Update(void);

    /*!
     *  @brief      描画
     */
    void    Draw(void);

    /*!
     *  @brief      解放
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
    static const float	            m_effect_speed;    //!< エフェクトの表示位置の移動速度
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
