#pragma once

#include "vivid.h"
#include "..\ui.h"
class CTextOverview : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CTextOverview(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CTextOverview(void);

    /*!
     *  @brief      ������
     */
    void        Initialize();

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
    static const vivid::Vector2     m_position;         //!< �ʒu

    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const vivid::Rect        m_rect;             //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;           //!< ��_
    static const vivid::Vector2     m_scale;            //!< �g�k

};