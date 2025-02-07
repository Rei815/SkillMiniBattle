#pragma once

#include "vivid.h"
#include "..\ui.h"
class CTitleButton : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CTitleButton(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CTitleButton(void);

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

private:
    static const vivid::Vector2     m_position;     //!< �ʒu
    static const int                m_height;       //!< ����
    static const int                m_width;        //!< ��
    static const vivid::Rect        m_rect;         //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;       //!< ��_
    static const vivid::Vector2     m_scale;        //!< �g�k

    unsigned int                    m_Color;
    static const int                m_fade_speed;
    int                             m_FadeSpeed;
};
