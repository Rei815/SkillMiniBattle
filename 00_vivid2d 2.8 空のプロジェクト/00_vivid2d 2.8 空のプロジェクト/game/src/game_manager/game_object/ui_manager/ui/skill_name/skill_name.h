#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../skill_manager/skill/skill_id.h"

class CSkillName : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CSkillName(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CSkillName(void);

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

    void        SetData(SKILL_ID skill_id, vivid::Vector2 position, float scale);
    void        SetData(SKILL_ID skill_id, vivid::Vector2 position, vivid::Vector2 scale);

    void        SetSkillInfo(SKILL_ID skill_id);

    void        SetPosition(const vivid::Vector2& position);

private:
    static const int                m_height;           //!< 高さ
    static const int                m_width;            //!< 幅
    static const vivid::Rect        m_rect;             //!< 読み込み範囲
    static const vivid::Vector2     m_anchor;           //!< 基準点
    static const vivid::Vector2     m_default_scale;    //!< 拡縮


    static const std::string        m_skill_info_file_name[];
    std::string                     m_FileName;
};
