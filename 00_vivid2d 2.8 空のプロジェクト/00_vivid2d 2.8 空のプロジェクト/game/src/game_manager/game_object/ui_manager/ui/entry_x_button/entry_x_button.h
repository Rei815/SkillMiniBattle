#pragma once

#include "vivid.h"
#include "..\ui.h"
class CEntryXButton : public CUI
{
public:
    enum class STATE
    {
        WAIT,
        FADE_IN,
        FADE_OUT,
    };
    /*!
     *  @brief      �R���X�g���N�^
     */
    CEntryXButton(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CEntryXButton(void);

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
    static const float              m_wait_time;    //!< �ҋ@����

    unsigned int                    m_Color[2];
    static const int                m_fade_speed;
    int                             m_FadeSpeed;
    int                             m_UINum;
    CTimer                          m_WaitTimer;
    STATE                           m_State;
};
