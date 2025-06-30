#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../scene_manager/scene/game/game_id.h"

class CGameVideo : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CGameVideo(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CGameVideo(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(void);

    /*!
     *  @brief      �X�V
     */
    void        Update(void);

    /*!
     *  @brief      �`��
     */
    void        Draw(void);

    /*!
     *  @brief      ���
     */
    void        Finalize(void);

    void        SetGameVideo(GAME_ID game_id);

private:
    static const int                m_height;                   //!< ����
    static const int                m_width;                    //!< ��
    static const float              m_scale;                    //!< �g�嗦
    static const vivid::Vector2     m_position;                 //!< �ʒu
    static const std::string        m_file_name[];   //!< �t�@�C����

    int                             m_Handle;                   //!< �n���h��
};
