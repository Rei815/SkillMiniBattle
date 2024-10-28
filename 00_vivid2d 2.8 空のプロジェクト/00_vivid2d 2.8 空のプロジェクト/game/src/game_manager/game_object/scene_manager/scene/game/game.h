#pragma once

#include"..\scene.h"
#include "../../../model_manager/model/model.h"
#include "../../../stage/stage.h"
#include "game_id.h"
#include "../../../object_manager/object/object.h"
/*!
*  @brief  ゲームの状態
*/
enum class GAME_STATE
{
    START,
    PLAY,
    FINISH,
};

class CGame
    : public IScene
{
public:

    /*!
     *  @brief      コンストラクタ
     */
    CGame(void);

    /*!
     *  @brief      デストラクタ
     */
    virtual ~CGame(void);

    /*!
     *  @brief      初期化
     */
    virtual void        Initialize(void);

    /*!
     *  @brief      更新
     */
    virtual void        Update(void);

    /*!
     *  @brief      描画
     */
    virtual void        Draw(void);

    /*!
     *  @brief      解放
     */
    virtual void        Finalize(void);

    /*!
     *  @brief      ゲームの状態取得
     *
     *  @return     ゲームの状態ID
     */
    GAME_STATE  GetGameState(void);

    /*!
     *  @brief      ゲームの状態設定
     *
     *  @param[in]  state   ゲーム状態ID
     */
    void        SetGameState(GAME_STATE state);


protected:


    /*!
     *  @brief      スタート
     */
    virtual void    Start(void);

    /*!
     *  @brief      プレイ
     */
    virtual void    Play(void);

    /*!
     *  @brief      終了
     */
    virtual void    Finish(void);

    GAME_STATE      m_GameState;    //!< ゲームの状態


    int             m_WaitTime;     //!< 待機時間
    bool            m_PauseFlag;    //!< ポーズフラグ
    std::string     m_DebugText;    //!< デバッグ用
    bool            m_SetActionflag;//!< プレイヤーアクションフラグ設定用

    /*!
     *  @brief      プレイヤーリスト型
     */
    using DEFEAT_LIST = std::list<CPlayer*>;

    DEFEAT_LIST     m_DefeatList;
};
