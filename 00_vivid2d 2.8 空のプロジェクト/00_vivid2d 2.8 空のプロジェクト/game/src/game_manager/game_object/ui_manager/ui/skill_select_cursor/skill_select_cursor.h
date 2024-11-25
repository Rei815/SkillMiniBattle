#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../skill_manager/skill/skill_id.h"
#include "../../../unit_manager/unit/unit_id.h"

class CSkillSelectCursor : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CSkillSelectCursor(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CSkillSelectCursor(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(void);

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

    void        SetCursor(UNIT_ID player_id, int PosNum);

private:
    static const vivid::Vector2     m_positionList[];   //!< 位置
    static const int                m_height;           //!< 高さ
    static const int                m_width;            //!< 幅
    static const vivid::Rect        m_rect;             //!< 読み込み範囲
    static const vivid::Vector2     m_anchor;           //!< 基準点
    static const vivid::Vector2     m_scale;            //!< 拡縮

    static const std::string        m_cursorFileName[];

    bool                            m_Selected;

    std::string                     m_FileName;
};
