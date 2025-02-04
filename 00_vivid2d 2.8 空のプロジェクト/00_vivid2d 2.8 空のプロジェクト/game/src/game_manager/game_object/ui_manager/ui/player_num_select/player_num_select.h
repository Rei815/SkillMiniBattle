#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../skill_manager/skill/skill_id.h"
#include "../../../unit_manager/unit/unit_id.h"

class CPlayerNumSelect : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CPlayerNumSelect(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CPlayerNumSelect(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(const vivid::Vector2& position);

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

    void        SetData(const vivid::Vector2& position, int player_num, vivid::Vector2 scale);
    void        SetData(const vivid::Vector2& position, int player_num, float scale);

    void        SetPosition(const vivid::Vector2& position);

    void        SetPlayerNum(int player_num);

    void        SetSelected(bool selected);

private:
    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const vivid::Rect        m_rect;             //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;           //!< ��_
    static const vivid::Vector2     m_default_scale;            //!< �g�k
    static const float              m_selected_scale_magnification;
    static const unsigned int       m_default_color;
    static const unsigned int       m_selected_color;

    static const std::string        m_file_name[];

    int m_PlayerNum;
    bool m_SelectedFlag;
};
