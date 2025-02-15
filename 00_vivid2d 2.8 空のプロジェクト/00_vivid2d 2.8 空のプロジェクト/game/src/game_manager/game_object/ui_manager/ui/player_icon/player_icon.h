#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../unit_manager/unit/unit_id.h"

class  CPlayerIcon :  public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CPlayerIcon(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CPlayerIcon(void);

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

    /*!
     *  @brief  プレイヤーのIDを設定
     *          IDで画像を差し替える
     */
    void        SetPlayerID(UNIT_ID unit_id);

private:

    static const vivid::Vector2     m_position;     //!< 位置
    static const int                m_height;       //!< 高さ
    static const int                m_width;        //!< 幅
    static const vivid::Rect        m_rect;         //!< 読み込み範囲
    static const vivid::Vector2     m_anchor;       //!< 基準点
    static const vivid::Vector2     m_scale;        //!< 拡縮

    static const std::string        m_file_name[];
    std::string                     m_FileName;
    int                             m_PlayerID;
};