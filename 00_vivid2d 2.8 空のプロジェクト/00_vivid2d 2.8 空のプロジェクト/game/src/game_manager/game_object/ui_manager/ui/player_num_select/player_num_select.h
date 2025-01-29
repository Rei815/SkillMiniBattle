#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../skill_manager/skill/skill_id.h"
#include "../../../unit_manager/unit/unit_id.h"

class CPlayerNumSelect : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CPlayerNumSelect(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CPlayerNumSelect(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(const vivid::Vector2& position);

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

    void        SetData(const vivid::Vector2& position, int player_num, vivid::Vector2 scale);
    void        SetData(const vivid::Vector2& position, int player_num, float scale);

    void        SetPosition(const vivid::Vector2& position);

    void        SetPlayerNum(int player_num);

    void        SetSelected(bool selected);

private:
    static const int                m_height;           //!< 高さ
    static const int                m_width;            //!< 幅
    static const vivid::Rect        m_rect;             //!< 読み込み範囲
    static const vivid::Vector2     m_anchor;           //!< 基準点
    static const vivid::Vector2     m_default_scale;            //!< 拡縮
    static const float              m_selected_scale_magnification;
    static const unsigned int       m_default_color;
    static const unsigned int       m_selected_color;

    static const std::string        m_file_name[];

    int m_PlayerNum;
    bool m_SelectedFlag;
};
