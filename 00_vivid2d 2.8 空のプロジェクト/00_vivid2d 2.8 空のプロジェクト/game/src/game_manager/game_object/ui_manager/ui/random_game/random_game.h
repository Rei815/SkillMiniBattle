#pragma once

#include "vivid.h"
#include "..\ui.h"
class CRandomGame : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CRandomGame(void);

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
    static const vivid::Vector2     m_position;     //!< �ʒu
    static const int                m_height;       //!< ����
    static const int                m_width;        //!< ��
    static const vivid::Rect        m_rect;         //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;       //!< ��_
    static const vivid::Vector2     m_scale;        //!< �g�k

    int                             m_Handle;
};
