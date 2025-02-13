#pragma once

#include "..\game.h"

class CBeltConveyorGame : public CGame
{
public:

    /*!
     *  @brief      コンストラクタ
     */
    CBeltConveyorGame(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CBeltConveyorGame(void);

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

    static const float m_defeat_height;

    static const CVector3   m_player_spawnpos_list[(int)UNIT_ID::NONE];
    static const CVector3   m_player_default_forward;

    static const CVector3   m_camera_position;
    static const CVector3   m_camera_direction;

    static const CVector3   m_belt_conveyor_position;
    static const float      m_belt_conveyor_rotate_y;
    static const float      m_belt_conveyor_scale;

    IObject*    m_StageObject;
};