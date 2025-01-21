#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../skill_manager/skill/skill_id.h"

class CSkillIcon : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CSkillIcon(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CSkillIcon(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(vivid::Vector2 position);
    
    /*!
     *  @brief      更新
     */
    void        Update(void);

    /*!
     *  @brief      描画
     */
    void        Draw(void);

    /*!
     *  @brief      解放
     */
    void        Finalize(void);

    void        SetIcon(SKILL_ID skill_id,vivid::Vector2 position, float scale);
    void        SetIcon(SKILL_ID skill_id,vivid::Vector2 position, vivid::Vector2 scale);

    void        SetSkill(SKILL_ID skill_id);

    void        SetPosition(vivid::Vector2 position);

    void        SetScale(float scale);
    void        SetScale(vivid::Vector2 scale);

    enum class ICON_BRIGHTNESS
    {
        BRIGHT,
        DARK,
    };

    void        SetBrightness(ICON_BRIGHTNESS icon_brightness);

private:
    static const int                m_height;           //!< 高さ
    static const int                m_width;            //!< 幅
    static const vivid::Rect        m_rect;             //!< 読み込み範囲
    static const vivid::Vector2     m_anchor;           //!< 基準点
    static const vivid::Vector2     m_default_scale;            //!< 拡縮
    static const unsigned int       m_brightness_color;
    static const unsigned int       m_dark_color;


    static const std::string        m_skill_icon_file_name[];
    std::string                     m_FileName;

    vivid::Vector2      m_Scale;
    vivid::Vector2      m_CenterPosition;

    ICON_BRIGHTNESS     m_Brightness;
};
