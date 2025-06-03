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
    static const int                    m_games_num;            //!< �Q�[����
    static const CVector3               m_camera_position;      //!< �J�����̈ʒu
    static const float                  m_circle_radius;        //!< �~�̔��a
    CSceneUIParent*                     m_PlaneUIParent;        //!< UI�̐e(��]�v���[��)
    CSceneUIParent*                     m_RevealUIParent;       //!< UI�̐e(�����pUI)
    CPlaneGameImage*                    m_SelectedPlane;        //!< ���ʂ̃Q�[���摜
    bool                                m_SelectedGameFlag;     //!< �Q�[�����I�΂ꂽ��
    bool                                m_GameInfomationFlag;   //!< �Q�[���̐������o����
    GAME_ID                             m_SelectedGameID;       //!< �I�΂ꂽ�Q�[����ID
};
