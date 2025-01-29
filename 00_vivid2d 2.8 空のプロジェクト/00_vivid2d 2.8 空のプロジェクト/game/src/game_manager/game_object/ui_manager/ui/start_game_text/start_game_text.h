#pragma once

#include "vivid.h"
#include "..\ui.h"

class CStartGameText : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CStartGameText(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CStartGameText(void);

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
    enum class START_TEXT_MOVE
    {
        ZOOM_IN,
        STOP,
        FADE_OUT,
    };

    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const vivid::Rect        m_rect;             //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;           //!< ��_
    static const vivid::Vector2     m_default_scale;    //!< �������̊g�k
    static const vivid::Vector2     m_max_scale;        //!< �ő�̊g�嗦
    static const vivid::Vector2     m_default_position; //!< �������̍��W
    static const unsigned int       m_default_color;    //!< �������̐F

    static const std::string        m_file_name;      //!< �J�E���g�_�E���̃t�@�C����

    static const float              m_zoomin_time;
    static const float              m_stop_time;
    static const float              m_fadeout_time;


    START_TEXT_MOVE                 m_MoveState;
    CTimer                          m_Timer;
    unsigned int                    m_Color;
};
