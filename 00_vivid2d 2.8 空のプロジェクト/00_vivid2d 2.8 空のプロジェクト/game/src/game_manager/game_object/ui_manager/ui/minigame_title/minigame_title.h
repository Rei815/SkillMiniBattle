#pragma once

#include "vivid.h"
#include "..\ui.h"
class CMiniGameTitle : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CMiniGameTitle(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CMiniGameTitle(void);

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
    static const int                m_height;       //!< ����
    static const int                m_width;        //!< ��

    static const std::string        m_file_name[];   //!< �t�@�C����
    std::string                     m_File_name;
};
