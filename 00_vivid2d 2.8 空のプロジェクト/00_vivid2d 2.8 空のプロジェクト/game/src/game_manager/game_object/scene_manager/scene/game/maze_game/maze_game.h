#pragma once

#include "..\game.h"
#include "../../../../light/light.h"

class CMazeGame : public CGame
{
public:

    /*!
     *  @brief      コンストラクタ
     */
    CMazeGame(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CMazeGame(void);

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

    static const CVector3           m_camera_position;          //!< カメラの位置
    static const CVector3           m_camera_direction;         //!< カメラの方向
    static const CVector3           m_player_default_forward;   //!< プレイヤーのスポーン時の正面方向
    static const CVector3           m_player_position[];   //!< プレイヤーの位置
    CLight                          m_Light;

};
