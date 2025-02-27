
/*!
 *  @file       scene_manager.h
 *  @brief      シーン管理
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"
#include"scene\scene_id.h"
#include <list>
#include "..\..\..\utility\utility.h"
#include "..\controller_manager\controller\controller.h"
#include"scene\game\game.h"

class IScene;
class CController;

/*!
 *  @class      CSceneManager
 *
 *  @brief      シーン管理クラス
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class CSceneManager
{
public:

    /*!
      *  @brief      インスタンスの取得
      *
      *  @return     インスタンス
      */
    static CSceneManager& GetInstance(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(void);

    /*!
     *  @brief      更新
     */
    void        Update(void);

    /*!
     *  @brief      描画
     */
    void        Draw(void);

    /*!
     *  @brief      シーンエフェクト描画
     */
    void        DrawSceneEffect(void);

    /*!
     *  @brief      解放
     */
    void        Finalize(void);

    /*!
     *  @brief      シーン切り換え
     *
     *  @param[in]  id  シーンID
     */
    void        ChangeScene(SCENE_ID id);

    /*!
     *  @brief      シーンをスタックする
     *
     *  @param[in]  id  シーンID
     */
    void        PushScene(SCENE_ID id);

    /*!
     *  @brief      スタックされたシーンを取り出す
     *
     *  @param[in]  id  シーンID
     */
    void        PopScene(SCENE_ID id);

    using SCENE_LIST = std::list<IScene*>;
    SCENE_LIST                  m_SceneList;            //!< シーンクラス

    SCENE_LIST  GetList();

    /*!
     *  @brief      ポーズ中か
     *
     *  @return     ポーズフラグ
     */
    bool            Pausing(void);
    /*!
     *  @brief      ポーズフラグ設定
     *
     *  @return     ポーズフラグ
     */
    void            SetPauseFlag(bool active);


    ///*!
    // *  @brief      最新のシーンのIDを取得
    // *
    // *  @return     最新のシーンのID
    // */
    SCENE_ID GetLastSceneID(void);

    void Pause();
private:
    /*!
     *  @brief      コンストラクタ
     */
    CSceneManager(void);

    /*!
     *  @brief      コピーコンストラクタ
     *
     *  @param[in]  rhs     オブジェクト
     */
    CSceneManager(const CSceneManager& rhs);

    /*!
     *  @brief      デストラクタ
     */
    ~CSceneManager(void);

    /*!
     *  @brief      代入演算子
     *
     *  @param[in]  rhs 代入オブジェクト
     *
     *  @return     自身のオブジェクト
     */
    CSceneManager& operator=(const CSceneManager& rhs);

    /*!
     *  @brief      シーン生成
     *
     *  @param[in]  id  シーンID
     */
    IScene*     CreateScene(SCENE_ID id);

    /*!
     *  @brief      フェードイン
     */
    void        FadeIn(void);

    /*!
     *  @brief      シーン更新
     */
    void        SceneUpdate(void);

    /*!
     *  @brief      フェードアウト
     */
    void        FadeOut(void);

    /*!
     *  @brief      シーン変更
     */
    void        SceneChange();

    /*!
     *  @brief      シーン取得
     */
    IScene*     GetScene(SCENE_ID scene_id);


    /*!
     *  @brief      状態ID
     */
    enum class STATE
    {
        FADEIN,          //!< フェードイン
        SCENE_UPDATE,    //!< シーン更新
        FADEOUT,         //!< フェードアウト
        SCENE_CHANGE    //!< シーン変更
    };

    static const int            m_fade_speed;       //!< フェード速度
    static const float          m_wait_time;    //!< アルファ値が最大になった時の待機時間

    SCENE_ID                    m_CurrentSceneID;   //!< 現在のシーンID
    SCENE_ID                    m_NextSceneID;      //!< 次のシーンID

    STATE                       m_State;            //!< 状態
    bool                        m_ChangeScene;      //!< シーン変更フラグ
    int                         m_FadeAlpha;        //!< フェード時のアルファ値
    unsigned int                m_FadeColor;
    int                         m_FadeSpeed;
    CTimer                      m_Timer;
    bool                        m_PauseFlag;    //!< ポーズフラグ
    CController*                m_PauseController;

};
