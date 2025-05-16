#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include "../../../ui_manager/ui/scene_ui_parent/scene_ui_parent.h"
#include "../../../ui_manager/ui/plane_game_image/plane_game_image.h"


class CGameRollAndReveal
    : public IScene
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CGameRollAndReveal(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CGameRollAndReveal(void);

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
    static const int    m_games_num;
    static const float  m_circle_radius;
    CSceneUIParent*     m_FirstSceneUIParent;
    CSceneUIParent*     m_SecondSceneUIParent;
    CPlaneGameImage*    m_PlaneGameImage;
    bool                m_SelectedGameFlag;
    bool                m_GameInfomationFlag;
    GAME_ID             m_SelectedGameID;
};
