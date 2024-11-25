
/*!
 *  @file       scene.h
 *  @brief      シーンベース
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once
#include "scene_id.h"

enum class SCENE_STATE
{
    WAIT,
    ACTIVE,
};

class IScene
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    IScene(void);

    /*!
     *  @brief      デストラクタ
     */
    virtual ~IScene(void);

    /*!
     *  @brief      初期化
     */
    virtual void        Initialize(SCENE_ID scene_id);

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

    bool        GetActive();

    SCENE_ID    GetSceneID();

    SCENE_STATE GetSceneState();
    void        SetSceneState(SCENE_STATE state);
protected:
    bool        m_Active;
    SCENE_ID    m_SceneID;
    SCENE_STATE m_State;
};
