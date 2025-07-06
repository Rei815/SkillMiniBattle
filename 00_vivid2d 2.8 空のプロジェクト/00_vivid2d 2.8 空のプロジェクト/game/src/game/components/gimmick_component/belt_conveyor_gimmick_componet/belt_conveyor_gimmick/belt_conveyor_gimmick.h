#pragma once
#include "../../../../../engine/utility/utility.h"
#include "../../../../../engine/core/game_object/game_object.h"
#include <list>
class CBeltConveyorGimmick
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     */
    CBeltConveyorGimmick();

    /*!
     *  @brief      デストラクタ
     */
    ~CBeltConveyorGimmick(void);

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

private:
    static const float      m_mid_belt_speed_time;

    static const float      m_default_belt_move_speed;
    static const float      m_min_belt_speed_rate;
    static const float      m_mid_belt_speed_rate;
    static const float      m_max_belt_speed_rate;
    float                   m_NowBeltSpeedRate;
    CVector3                m_BeltConveyorForward;
    CTimer                  m_Timer;
    CTimer                  m_ObstructionSpawnTimer;
    static const float      m_default_obstruction_spawn_time;

    static const float      m_obstruction_object_scale;
    static const CVector3   m_obstruction_spawn_relative_pos;
    static const float      m_obstruction_delete_height;

    static const float      m_obstruction_object_fall_speed;

    std::list<std::shared_ptr<CGameObject>>     m_ObstructionObjectList;
    CGameObject* m_Object;
    bool                            m_OperationFlag;

};
