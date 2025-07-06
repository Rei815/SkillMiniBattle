#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../skill_manager/skill/skill_id.h"
#include "../../../../../game/components/player_component/player_id.h"

class CSkillCursor : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CSkillCursor(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CSkillCursor(void);

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

    void        SetCursor(PLAYER_ID player_id, vivid::Vector2 position, float scale);
    void        SetCursor(PLAYER_ID player_id, vivid::Vector2 position, vivid::Vector2 scale);

    void        SetPlayer(PLAYER_ID player_id);

    void        SetPosition(const vivid::Vector2& position);

private:
    static const int                m_height;           //!< 高さ
    static const int                m_width;            //!< 幅
    static const vivid::Rect        m_rect;             //!< 読み込み範囲
    static const vivid::Vector2     m_anchor;           //!< 基準点
    static const vivid::Vector2     m_default_scale;            //!< 拡縮

    static const std::string        m_cursorFileName[];

    bool                            m_Selected;

    std::string                     m_FileName;
};
