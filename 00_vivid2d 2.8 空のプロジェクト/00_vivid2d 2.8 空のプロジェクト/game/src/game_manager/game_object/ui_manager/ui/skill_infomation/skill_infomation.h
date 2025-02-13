#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../skill_manager/skill/skill_id.h"

class CSkillInfomation : public CUI
{
public:
    /*!
     *  @brief      ƒRƒ“ƒXƒgƒ‰ƒNƒ^
     */
    CSkillInfomation(UI_ID id);

    /*!
     *  @brief      ƒfƒXƒgƒ‰ƒNƒ^
     */
    ~CSkillInfomation(void);

    /*!
     *  @brief      ‰Šú‰»
     */
    void        Initialize(void);

    /*!
     *  @brief      ‰Šú‰»
     */
    void        Initialize(vivid::Vector2 position);

    /*!
     *  @brief      XV
     */
    void        Update(void);

    /*!
     *  @brief      •`‰æ
     */
    void        Draw(void);

    /*!
     *  @brief      ‰ğ•ú
     */
    void        Finalize(void);

    void        SetData(SKILL_ID skill_id, vivid::Vector2 position, float scale);
    void        SetData(SKILL_ID skill_id, vivid::Vector2 position, vivid::Vector2 scale);

    void        SetSkillInfo(SKILL_ID skill_id);

    void        SetPosition(const vivid::Vector2& position);

private:
    static const int                m_height;           //!< ‚‚³
    static const int                m_width;            //!< •
    static const vivid::Rect        m_rect;             //!< “Ç‚İ‚İ”ÍˆÍ
    static const vivid::Vector2     m_anchor;           //!< Šî€“_
    static const vivid::Vector2     m_default_scale;    //!< Šgk


    static const std::string        m_skill_info_file_name[];
    std::string                     m_FileName;

    static const int                m_bg_height;           //!< ”wŒi‚‚³
    static const int                m_bg_width;            //!< ”wŒi•
    static const vivid::Rect        m_bg_rect;             //!< ”wŒi“Ç‚İ‚İ”ÍˆÍ
    static const vivid::Vector2     m_bg_anchor;           //!< ”wŒiŠî€“_
    static const vivid::Vector2     m_bg_shift_pos;        //!< ”wŒiÀ•W‚Ì‚¸‚ê
    static const std::string        m_skill_info_bg_file_name;
};
