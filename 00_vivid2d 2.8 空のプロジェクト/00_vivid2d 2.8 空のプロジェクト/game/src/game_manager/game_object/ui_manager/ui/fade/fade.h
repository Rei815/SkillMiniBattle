#pragma once

#include "vivid.h"
#include "..\ui.h"
class CFade : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CFade(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CFade(void);

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
    static const std::string        m_file_name;        //!< �t�@�C����

    static const vivid::Vector2     m_position;     //!< �ʒu
    static const int                m_height;       //!< ����
    static const int                m_width;        //!< ��
    static const float              m_wait_time;    //!< �A���t�@�l���ő�ɂȂ������̑ҋ@����
    unsigned int                    m_Color;
    static const int                m_fade_speed;
    int                             m_FadeSpeed;
    CTimer                          m_Timer;
};