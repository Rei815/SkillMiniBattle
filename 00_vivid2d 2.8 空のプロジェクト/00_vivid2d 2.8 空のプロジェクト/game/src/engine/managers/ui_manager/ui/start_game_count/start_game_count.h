#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../../utility/timer/timer.h"

class CStartGameCount : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CStartGameCount(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CStartGameCount(void);

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
    enum class START_COUNT_MOVE
    {
        MOVE_IN,
        STOP,
        MOVE_OUT,
    };

    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const vivid::Rect        m_rect;             //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;           //!< ��_
    static const vivid::Vector2     m_default_scale;    //!< �g�k
    static const vivid::Vector2     m_max_scale;        //!< �ő�̊g�嗦

    static const std::string        m_file_name[];      //!< �J�E���g�_�E���̃t�@�C����

    static const float              m_movein_time;
    static const float              m_stop_time;
    static const float              m_moveout_time;

    static const vivid::Vector2     m_movein_position;      //!< �������̍��W
    static const float              m_stop_position_y;      //!< ��~���鎞��y���W
    static const float              m_moveout_position_y;   //!< ���Ŏ���y���W

    START_COUNT_MOVE                m_MoveState;
    CTimer                          m_Timer;
    int                             m_CountDown;
};
