#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "..\..\..\..\..\mathematics\mathematics.h"
class CRandomGame : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CRandomGame(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CRandomGame(void);

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


    static const TCHAR*             m_file_name;
    static const CVector3           m_initial_position;     //!< �����ʒu
    static const int                m_height;       //!< ����
    static const int                m_width;        //!< ��
    static const vivid::Rect        m_rect;         //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;       //!< ��_
    static const vivid::Vector2     m_scale;        //!< �g�k
    static const float              m_rotation_speed;
    static const float              m_speed;
    int                             m_Width;
    int                             m_Height;
    int                             m_Handle;
    float                           m_Angle;
    float                           m_PosAngle;
};
