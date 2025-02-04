#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include "../../../ui_manager/ui/scene_ui_parent/scene_ui_parent.h"
#include "..\..\..\ui_manager\ui\player_num_select\player_num_select.h"

class CSelectPlayer
    : public IScene
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CSelectPlayer(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSelectPlayer(void);

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
    static const vivid::Vector2 m_player_num_ui_pos[(int)UNIT_ID::NONE];
    static const float          m_player_num_ui_scale;

    CPlayerNumSelect* m_PlayerNumUI[(int)UNIT_ID::NONE];
    CSceneUIParent* m_SceneUIParent;

};
