#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../scene_manager/scene/scene_id.h"

class CSceneTitle : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CSceneTitle(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSceneTitle(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(vivid::Vector2 position);

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

    void        SetData(SCENE_ID scene_id, vivid::Vector2 position, float scale);
    void        SetData(SCENE_ID scene_id, vivid::Vector2 position, vivid::Vector2 scale);

    void        SetSceneInfo(SCENE_ID scene_id);

    void        SetPosition(const vivid::Vector2& position);

private:
    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const vivid::Rect        m_rect;             //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;           //!< ��_
    static const vivid::Vector2     m_default_scale;    //!< �g�k
    static const vivid::Vector2     m_default_position;


    static const std::string        m_scene_title_file_name[(int)SCENE_ID::MAX];
    std::string                     m_FileName;
};
