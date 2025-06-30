#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../unit_manager/unit/unit_id.h"

class  CPlayerIcon :  public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CPlayerIcon(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CPlayerIcon(void);

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
     *  @brief  �v���C���[��ID��ݒ�
     *          ID�ŉ摜�������ւ���
     */
    void        SetPlayerID(UNIT_ID unit_id);

private:

    static const vivid::Vector2     m_position;     //!< �ʒu
    static const int                m_height;       //!< ����
    static const int                m_width;        //!< ��
    static const vivid::Rect        m_rect;         //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;       //!< ��_
    static const vivid::Vector2     m_scale;        //!< �g�k

    static const std::string        m_file_name[];
    std::string                     m_FileName;
    int                             m_PlayerID;
};