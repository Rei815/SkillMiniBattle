#pragma once

#include "..\game.h"
#include "..\..\..\..\ui_manager\ui\ui_id.h"
#include "../../../../sound_manager/sound_manager.h"


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
    void Initialize(SCENE_ID scene_id);
    
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

    /*!
     *  @brief      終了判定
     */
    void    CheckFinish(void) override;

    void SpawnCannnon(void);

    IObject* ChooseCannon(void);


    static const CVector3   m_cannon_pos_list[];
    static const CVector3   m_cannon_rot_list[];
    static const CVector3   m_player_spawnpos_list[];
    static const CVector3   m_player_default_forward; //!< プレイヤーのスポーン時の正面方向

    static const int        m_max_cannnon_count;
    static const float      m_cannnon_spawn_time;
    static const float      m_initial_shot_time;
    static const float      m_min_shot_time;
    static const float      m_shot_time_acceleration;

    static const float      m_defeat_distance;

    static const float      m_stage_shrink_time;
    static const CVector3   m_default_stage_position;
    static const CVector3   m_default_stage_rotation;
    static const float      m_default_stage_scale;

    static const CVector3   m_camera_position;
    static const CVector3   m_camera_direction;

    int                 m_CannonCount;
    CTimer              m_SpawnTimer;
    CTimer              m_ShotTimer;
    float               m_NowShotTime;
    CTimer              m_StageShrinkTimer;
    bool                m_StageShrinkFlg;
    IObject*            m_StageObject;
    CANNON_DIRECTION    m_NextCannnonDir;
    CSoundManager*      m_bgm;
};
