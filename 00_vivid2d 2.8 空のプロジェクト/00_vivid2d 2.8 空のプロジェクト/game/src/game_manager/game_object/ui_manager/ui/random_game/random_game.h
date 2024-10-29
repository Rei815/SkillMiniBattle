#pragma once

#include "vivid.h"
#include "..\ui.h"
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

    void Draw3DRot(const CVector3& position, float _x_rot, float _y_rot, float _z_rot);

    static const TCHAR*             m_file_name;
    CVector3     m_Position;     //!< �ʒu
    static const int                m_height;       //!< ����
    static const int                m_width;        //!< ��
    static const vivid::Rect        m_rect;         //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;       //!< ��_
    static const vivid::Vector2     m_scale;        //!< �g�k
    static const float              m_rotation_speed;
    int                             m_Width;
    int                             m_Height;
    int                             m_Handle;
    float                           m_Angle;
};
