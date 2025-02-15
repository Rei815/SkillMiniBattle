#pragma once

#include "vivid.h"
#include "..\ui.h"
class CMiniGameManual : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CMiniGameManual(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CMiniGameManual(void);

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
    static const vivid::Vector2     m_bg_position;  //!< �w�i�̈ʒu
    static const vivid::Vector2     m_bg_scale;     //!< �w�i�̑傫��
    static const vivid::Vector2     m_manual_scale; //!< ��������̕����̑傫��

    static const int                m_height;       //!< ����
    static const int                m_width;        //!< ��

    static const std::string        m_file_name[];   //!< �t�@�C����
    std::string                     m_FileName;
};
