#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "..\fallout_select_bg\fallout_select_bg.h"
class CFallSelect : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CFallSelect(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CFallSelect(void);

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
    static const vivid::Vector2     m_positionList[];   //!< �ʒu
    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const vivid::Rect        m_rect;             //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;           //!< ��_
    static const vivid::Vector2     m_scale;            //!< �g�k
    static const float              m_speed;            //!< �����̑��x

    std::string                     m_FileName;
    vivid::Rect                     m_Rect;
    CFalloutSellectBG               m_BackGround;
};
