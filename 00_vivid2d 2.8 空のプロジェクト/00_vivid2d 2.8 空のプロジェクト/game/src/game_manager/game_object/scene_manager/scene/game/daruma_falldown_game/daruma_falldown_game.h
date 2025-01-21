#pragma once

#include "..\game.h"
#include "../../../../sound_manager/sound_manager.h"

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
 *  @brief      解放
 */
    void        Ranking(void);

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

    IObject* m_OgreObject;
    CTimer                          m_Timer;
    CVector3                        m_PlayerPosition[4];
    int                             m_RemainCount;
    int                             m_TempFirstNum;
    int                             m_CountTime;
    float                           m_TempFirstDis;
    bool                            m_GimmickOn;
    SOUND_ID                        m_Sound;
};