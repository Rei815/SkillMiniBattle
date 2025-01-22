#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../skill_manager/skill/skill_id.h"
#include "../../../unit_manager/unit/unit_id.h"

class CMenuBG : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CMenuBG(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CMenuBG(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(const vivid::Vector2& position);

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

    void        SetPosition(vivid::Vector2 position);

    void        SetScale(float scale);
    void        SetScale(vivid::Vector2 scale);

private:
    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const vivid::Rect        m_rect;             //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;           //!< ��_
    static const vivid::Vector2     m_default_scale;            //!< �g�k

    static const std::string        m_file_name;

    vivid::Vector2      m_Scale;
    vivid::Vector2      m_CenterPosition;
};
