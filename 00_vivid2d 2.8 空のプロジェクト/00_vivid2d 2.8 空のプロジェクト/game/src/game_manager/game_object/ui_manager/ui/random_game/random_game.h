#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "..\..\..\scene_manager\scene\game\game_id.h"
#include "..\..\..\..\..\primitive\primitive.h"

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
     *  @brief      ������
     */
    void        Initialize(const CTransform& transform);

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


    void        SetGameID(GAME_ID game_id);
private:


    static const std::string        m_file_names[];
    static const int                m_height;       //!< ����
    static const int                m_width;        //!< ��
    static const vivid::Rect        m_rect;         //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;       //!< ��_
    static const vivid::Vector2     m_scale;        //!< �g�k
    static const float              m_rotation_speed;
    static const float              m_speed;

    std::string                     m_FileName;
    int                             m_Width;
    int                             m_Height;
    int                             m_Handle;
    float                           m_Angle;
    float                           m_PosAngle;
    CPlane                          m_Plane;
    CVector3                        m_InitialPosition;     //!< �����ʒu
};
