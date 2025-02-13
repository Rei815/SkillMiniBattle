#pragma once

#include "vivid.h"
#include "..\ui.h"
class CGameBG : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CGameBG(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CGameBG(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(const std::string file_name);

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

private:
    static const vivid::Vector2     m_position;     //!< 位置
    static const int                m_height;       //!< 高さ
    static const int                m_width;        //!< 幅
    static const vivid::Rect        m_rect;         //!< 読み込み範囲
    static const vivid::Vector2     m_anchor;       //!< 基準点
    static const vivid::Vector2     m_scale;        //!< 拡縮

    std::string                     m_FileName;
};
