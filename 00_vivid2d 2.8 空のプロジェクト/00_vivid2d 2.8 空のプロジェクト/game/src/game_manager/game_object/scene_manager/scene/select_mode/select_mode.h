#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include "../../../ui_manager/ui/scene_ui_parent/scene_ui_parent.h"

class CSelectMode
    : public IScene
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CSelectMode(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSelectMode(void);

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
    CSceneUIParent* m_SceneUIParent;

};
