
/*!
 *  @file       scene.cpp
 *  @brief      シーンベース
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "scene.h"
#include "../scene_manager.h"

 /*
  *  コンストラクタ
  */
IScene::IScene(void)
    : m_ActiveFlag(true)
    , m_State(SCENE_STATE::ACTIVE)
{
}

/*
 *  デストラクタ
 */
IScene::~IScene(void)
{
}

/*
 *  初期化
 */
void
IScene::Initialize(SCENE_ID scene_id)
{
    m_SceneID = scene_id;
    m_State = SCENE_STATE::ACTIVE;
}

/*
 *  更新
 */
void
IScene::Update(void)
{

}

/*
 *  描画
 */
void
IScene::Draw(void)
{
}

/*
 *  解放
 */
void
IScene::Finalize(void)
{
    m_ActiveFlag = false;
}

bool IScene::GetActive()
{
    return m_ActiveFlag;
}

void IScene::SetActive(bool active)
{
    m_ActiveFlag = active;
}

SCENE_ID IScene::GetSceneID()
{
    return m_SceneID;
}


SCENE_STATE IScene::GetSceneState()
{
    return m_State;
}

void IScene::SetSceneState(SCENE_STATE state)
{
    m_State = state;
}

void IScene::Push(SCENE_ID id)
{
    CSceneManager::GetInstance().PushScene(id);

    m_State = SCENE_STATE::WAIT;
}

void IScene::Pop(SCENE_ID id)
{
    CSceneManager::GetInstance().PopScene(id);
}
