#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../skill_manager/skill/skill_id.h"

class CSkillIcon : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CSkillIcon(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSkillIcon(void);

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

    void        SetIcon(SKILL_ID skill_id,vivid::Vector2 position, float scale);
    void        SetIcon(SKILL_ID skill_id,vivid::Vector2 position, vivid::Vector2 scale);

    void        SetSkill(SKILL_ID skill_id);

    void        SetPosition(vivid::Vector2 position);
    void        SetCenterPosition(vivid::Vector2 position);

    void        SetScale(float scale);
    void        SetScale(vivid::Vector2 scale);

    enum class ICON_BRIGHTNESS
    {
        BRIGHT,
        DARK,
    };

    void        SetBrightness(ICON_BRIGHTNESS icon_brightness);

private:
    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const vivid::Rect        m_rect;             //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;           //!< ��_
    static const vivid::Vector2     m_default_scale;            //!< �g�k
    static const unsigned int       m_brightness_color;
    static const unsigned int       m_dark_color;


    static const std::string        m_skill_icon_file_name[];
    std::string                     m_FileName;

    vivid::Vector2      m_CenterPosition;

    ICON_BRIGHTNESS     m_Brightness;
};
