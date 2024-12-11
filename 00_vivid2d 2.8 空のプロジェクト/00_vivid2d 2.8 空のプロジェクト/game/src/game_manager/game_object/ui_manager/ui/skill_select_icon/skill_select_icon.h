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

    void        SetIcon(SKILL_ID skill_id,vivid::Vector2 position, float scale);
    void        SetIcon(SKILL_ID skill_id,vivid::Vector2 position, vivid::Vector2 scale);

    void        SetSkill(SKILL_ID skill_id);

    void        SetPosition(vivid::Vector2 position);

    void        SetScale(float scale);
    void        SetScale(vivid::Vector2 scale);

private:
    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const vivid::Rect        m_rect;             //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_default_anchor;           //!< ��_
    static const vivid::Vector2     m_default_scale;            //!< �g�k

    static const std::string        m_SkillIconFileName[];
    std::string                     m_FileName;

    vivid::Vector2      m_Anchor;
    vivid::Vector2      m_Scale;
    vivid::Vector2      m_CenterPosition;
};
