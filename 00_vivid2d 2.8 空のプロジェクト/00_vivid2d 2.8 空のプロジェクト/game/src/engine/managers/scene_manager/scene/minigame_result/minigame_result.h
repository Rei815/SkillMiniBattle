#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include "../../../ui_manager/ui/scene_ui_parent/scene_ui_parent.h"

class CMiniGameResult : public IScene
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CMiniGameResult(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CMiniGameResult(void);

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
    static const vivid::Vector2     m_origin_key_pos;
    static const vivid::Vector2     m_origin_icon_pos;
    static const vivid::Vector2     m_origin_notice_pos;
    static const float              m_key_offset;           //�����m�̋���
    static const float              m_icon_offset;          //�A�C�R�����m�̋���
    static const float              m_notice_offset;        //���莆���m�̋���
    static const float              m_players_key_offset;   //�v���C���[�Ԃ̌��̋���
    static const vivid::Vector2     m_notice_scale;         //���莆�̑傫��
    std::shared_ptr<CSceneUIParent> m_SceneUIParent;

};
