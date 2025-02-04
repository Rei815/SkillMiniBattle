#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../skill_manager/skill/skill_id.h"

class CSkillInfomation : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CSkillInfomation(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSkillInfomation(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(vivid::Vector2 position);

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

    void        SetData(SKILL_ID skill_id, vivid::Vector2 position, float scale);
    void        SetData(SKILL_ID skill_id, vivid::Vector2 position, vivid::Vector2 scale);

    void        SetSkillInfo(SKILL_ID skill_id);

    void        SetPosition(const vivid::Vector2& position);

private:
    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const vivid::Rect        m_rect;             //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;           //!< ��_
    static const vivid::Vector2     m_default_scale;    //!< �g�k


    static const std::string        m_skill_info_file_name[];
    std::string                     m_FileName;
};
