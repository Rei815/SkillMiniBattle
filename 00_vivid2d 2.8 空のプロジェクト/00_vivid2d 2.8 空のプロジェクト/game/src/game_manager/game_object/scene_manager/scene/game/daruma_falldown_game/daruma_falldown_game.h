#pragma once

#include "..\game.h"
#include "../../../../unit_manager/unit/player/player.h"


class CDaruma_FallDownGame : public CGame
{
public:
	CDaruma_FallDownGame();
	~CDaruma_FallDownGame();

    /*!
     *  @brief      初期化
     */
    void        Initialize(SCENE_ID scene_id);

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

    /*!
     *  @brief      ゲーム終了、リザルト画面へ
     */
    void        Ranking(void);

    /*!
     *  @brief      ゲーム終了、リザルト画面へ
     */
    void        ResetPosition(void);

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

    static const CVector3           m_camera_position;          //カメラのポジション
    static const CVector3           m_camera_direction;         //カメラの角度
    static const CVector3           m_ogre_position;            //鬼のポジション
    static const CVector3           m_ogre_rotation;
    static const float              m_move_speed;
    static const CVector3           m_player_default_forward;   //プレイヤーのスポーン時の正面方向
    static const CVector3           m_goal_position;
    static const CVector3           m_reset_speed;

    IObject* m_OgreObject;
    CTimer                          m_Timer;
    CVector3                        m_PlayerPosition[4];
    CVector3                        m_StartPosition[4];
    int                             m_RemainCount;
    int                             m_TempFirstNum;
    int                             m_CountTime;
    int                             m_TextureColor[4];
    float                           m_TempFirstDis;
    bool                            m_GimmickOn;
    std::list<CPlayer*>             m_MovePlayer;
    vivid::Vector2                  m_TextPosition;
};