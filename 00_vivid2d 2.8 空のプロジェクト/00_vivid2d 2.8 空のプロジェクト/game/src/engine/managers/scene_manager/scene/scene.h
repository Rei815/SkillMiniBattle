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
    virtual void    Initialize(SCENE_ID scene_id);

    /*!
     *  @brief      更新
     */
    virtual void    Update(void);

    /*!
     *  @brief      描画
     */
    virtual void    Draw(void);

    /*!
     *  @brief      解放
     */
    virtual void    Finalize(void);


    bool            IsActive();

    void            Delete();

    SCENE_ID        GetSceneID();

    SCENE_STATE     GetSceneState();

    void            SetSceneState(SCENE_STATE state);

protected:

    /*!
        *  @brief      シーンをスタックする
        *
        *  @param[in]  id      シーンID
        */
    void    Push(SCENE_ID id);

    /*!
     *  @brief      スタックされたシーンを取り出す
     */
    void    Pop(SCENE_ID id);
    bool        m_ActiveFlag;
    SCENE_ID    m_SceneID;
    SCENE_STATE m_State;

};
