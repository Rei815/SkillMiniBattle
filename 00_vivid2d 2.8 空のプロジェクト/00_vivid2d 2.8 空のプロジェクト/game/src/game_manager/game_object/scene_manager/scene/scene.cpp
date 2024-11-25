
/*!
 *  @file       scene.cpp
 *  @brief      �V�[���x�[�X
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "scene.h"

 /*
  *  �R���X�g���N�^
  */
IScene::IScene(void)
    : m_Active(true)
    , m_State(SCENE_STATE::ACTIVE)
{
}

/*
 *  �f�X�g���N�^
 */
IScene::~IScene(void)
{
}

/*
 *  ������
 */
void
IScene::Initialize(SCENE_ID scene_id)
{
    m_SceneID = scene_id;
    m_State = SCENE_STATE::ACTIVE;
}

/*
 *  �X�V
 */
void
IScene::Update(void)
{

}

/*
 *  �`��
 */
void
IScene::Draw(void)
{
}

/*
 *  ���
 */
void
IScene::Finalize(void)
{
    m_Active = false;
}

bool IScene::GetActive()
{
    return m_Active;
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