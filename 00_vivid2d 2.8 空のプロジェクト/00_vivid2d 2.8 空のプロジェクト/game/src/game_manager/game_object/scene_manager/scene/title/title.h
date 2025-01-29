#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include "../../../stage/stage.h"
#include "../../../ui_manager/ui/scene_ui_parent/scene_ui_parent.h"

class CTitle
    : public IScene
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CTitle(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CTitle(void);

    /*!
     *  @brief      ������
     */
    void Initialize(SCENE_ID scene_id);

    /*!
     *  @brief      �X�V
     */
    void Update(void);

    /*!
     *  @brief      �`��
     */
    void Draw(void);

    /*!
     *  @brief      ���
     */
    void Finalize(void);

private:

    unsigned int        m_Color;
    static const int    m_fade_speed;
    int                 m_FadeSpeed;
    CSceneUIParent*     m_SceneUIParent;
};
