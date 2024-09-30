
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

class IScene;

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
     *  @brief      現在のシーンを取得
     *
     *  @return     現在のシーン
     */
    IScene* GetScene(void);

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
    void    CreateScene(SCENE_ID id);

    /*!
     *  @brief      フェードイン
     */
    void    FadeIn(void);

    /*!
     *  @brief      シーン更新
     */
    void    SceneUpdate(void);

    /*!
     *  @brief      フェードアウト
     */
    void    FadeOut(void);

    /*!
     *  @brief      シーン変更
     */
    void    SceneChange(void);

    /*!
     *  @brief      状態ID
     */
    enum class STATE
    {
        FADEIN          //!< フェードイン
        , SCENE_UPDATE    //!< シーン更新
        , FADEOUT         //!< フェードアウト
        , SCENE_CHANGE    //!< シーン変更
    };

    static const int            m_fade_speed;       //!< フェード速度
    static const vivid::Vector2 m_fade_position;    //!< フェード表示位置
    static const unsigned int   m_fade_color;       //!< フェード色
    static const int            m_min_fade_alpha;   //!< フェード用アルファの最小値
    static const int            m_max_fade_alpha;   //!< フェード用アルファの最大値
    SCENE_ID                    m_CurrentSceneID;   //!< 現在のシーンID
    SCENE_ID                    m_NextSceneID;      //!< 次のシーンID
    IScene*                     m_Scene;            //!< シーンクラス
    STATE                       m_State;            //!< 状態
    bool                        m_ChangeScene;      //!< シーン変更フラグ
    int                         m_FadeAlpha;        //!< フェード時のアルファ値
};
