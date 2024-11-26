#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../skill_manager/skill/skill_id.h"
#include "../../../unit_manager/unit/unit_id.h"

class CSkillSelectCursor : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CSkillSelectCursor(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSkillSelectCursor(void);

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

    void        SetCursor(UNIT_ID player_id, int PosNum);

private:
    static const vivid::Vector2     m_positionList[];   //!< �ʒu
    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const vivid::Rect        m_rect;             //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;           //!< ��_
    static const vivid::Vector2     m_scale;            //!< �g�k

    static const std::string        m_cursorFileName[];

    bool                            m_Selected;

    std::string                     m_FileName;
};
