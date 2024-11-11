#pragma once

#include "..\game.h"
#include "..\..\..\..\ui_manager\ui\ui_id.h"

enum class CANNON_DIRECTION
{
    UP,
    DOWN,
    RIGHT,
    LEFT,

    MAX,
};

class CDodgeBallGame : public CGame
{
public:

    /*!
     *  @brief      コンストラクタ
     */
    CDodgeBallGame(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CDodgeBallGame(void);

    /*!
     *  @brief      初期化
     */
    void Initialize(void);
    
    /*!
     *  @brief      更新
     */
    void        Update(void);

    /*!
     *  @brief      描画
     */
    void        Draw(void);

    /*!
     *  @brief      解放
     */
    void        Finalize(void);

private:
    /*!
     *  @brief      スタート
     */
    void    Start(void);

    /*!
     *  @brief      プレイ
     */
    void    Play(void);

    /*!
     *  @brief      終了
     */
    void    Finish(void);

    void SpawnCannnon(void);

    IObject* ChooseCannon(void);


    static const CVector3 m_cannon_pos_list[];
    static const CVector3 m_cannon_rot_list[];

    static const int        m_max_cannnon_count;
    static const float      m_cannnon_spawn_time;
    static const float      m_initial_shot_time;
    static const float      m_min_shot_time;
    static const float      m_shot_time_acceleration;

    static const float      m_defeat_distance;

    static const CVector3   m_camera_position;
    static const CVector3   m_camera_direction;

    int                 m_CannonCount;
    CTimer              m_SpawnTimer;
    CTimer              m_ShotTimer;
    float               m_NowShotTime;
    CANNON_DIRECTION    m_NextCannnonDir;

    CVector3 Test;
};
