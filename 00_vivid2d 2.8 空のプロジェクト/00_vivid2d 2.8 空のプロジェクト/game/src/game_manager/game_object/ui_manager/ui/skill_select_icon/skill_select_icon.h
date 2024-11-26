#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../skill_manager/skill/skill_id.h"

class CSkillSelectIcon : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CSkillSelectIcon(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSkillSelectIcon(void);

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

    void        SetIcon(SKILL_ID_FALLGAME skill_id, int PosNum);
    void        SetIcon(SKILL_ID_DARUMA skill_id, int PosNum);
    void        SetIcon(SKILL_ID_DODGEBALL skill_id, int PosNum);

private:
    static const vivid::Vector2     m_positionList[];   //!< �ʒu
    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const vivid::Rect        m_rect;             //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;           //!< ��_
    static const vivid::Vector2     m_scale;            //!< �g�k

    static const std::string        m_fallgameFileName[];
    static const std::string        m_darumaFileName[];
    static const std::string        m_dodgeballFileName[];

    bool                            m_Selected;

    std::string                     m_FileName;
};
