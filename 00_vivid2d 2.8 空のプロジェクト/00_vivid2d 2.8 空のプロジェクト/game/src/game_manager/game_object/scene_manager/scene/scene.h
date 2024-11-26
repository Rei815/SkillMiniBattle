
/*!
 *  @file       scene.h
 *  @brief      �V�[���x�[�X
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
     *  @brief      �R���X�g���N�^
     */
    IScene(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    virtual ~IScene(void);

    /*!
     *  @brief      ������
     */
    virtual void        Initialize(SCENE_ID scene_id);

    /*!
     *  @brief      �X�V
     */
    virtual void        Update(void);

    /*!
     *  @brief      �`��
     */
    virtual void        Draw(void);

    /*!
     *  @brief      ���
     */
    virtual void        Finalize(void);


    bool        GetActive();

    void        SetActive(bool active);

    SCENE_ID    GetSceneID();

    SCENE_STATE GetSceneState();
    void        SetSceneState(SCENE_STATE state);
protected:

    /*!
        *  @brief      �V�[�����X�^�b�N����
        *
        *  @param[in]  id      �V�[��ID
        */
    void    Push(SCENE_ID id);

    /*!
     *  @brief      �X�^�b�N���ꂽ�V�[�������o��
     */
    void    Pop(SCENE_ID id);
    bool        m_ActiveFlag;
    SCENE_ID    m_SceneID;
    SCENE_STATE m_State;
};
