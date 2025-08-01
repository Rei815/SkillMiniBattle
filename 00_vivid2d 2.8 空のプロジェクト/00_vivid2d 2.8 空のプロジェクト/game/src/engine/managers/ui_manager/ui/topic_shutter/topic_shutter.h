#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../../utility/timer/timer.h"
class CTopicShutter : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CTopicShutter(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CTopicShutter(void);

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

private:
    static const std::string        m_file_name;
    static const int                m_height;           //!< 高さ
    static const int                m_width;            //!< 幅
    static const int                m_speed;            //!< 上下するスピード
    static const vivid::Rect        m_rect;             //!< 読み込み範囲
    static const vivid::Vector2     m_anchor;           //!< 基準点
    static const vivid::Vector2     m_scale;            //!< 拡縮
    static const vivid::Vector2     m_adjust_value;     //!< 調整値
    static const float              m_duration_time;    //!< 隠す時間
    vivid::Rect                     m_Rect;             //!< 読み込み範囲

    CTimer                          m_Timer;
};