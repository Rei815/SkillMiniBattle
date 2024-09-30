#pragma once

#include "vivid.h"
#include "..\..\..\..\..\utility\utility.h"
#include "..\ui.h"

class CWaveClear : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CWaveClear(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CWaveClear(void);

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

    /*!
     *  @brief      ���S�ʒu�擾
     */
    vivid::Vector2        GetCenterPosition(void);


private:

    void        EaseOut(void);
    void        EaseIn(void);
    void        Reset(void);
    static const vivid::Vector2     m_position;         //!< �ʒu
    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const vivid::Rect        m_rect;             //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;           //!< ��_
    static const vivid::Vector2     m_scale;            //!< �g�k
    static const float              m_end_time;         //!< �I������
    static const float              m_relay_x;         //!< ���p�l
    static const float              m_end_x;           //!< �I���l

    float                           m_StartTime;        //!< �J�n����
    float                           m_StartValue;       //!< �J�n�l
    float                           m_FinishValue;      //!< �I���l
    CEasing                         m_Easing;           //!< �C�[�W���O
};
