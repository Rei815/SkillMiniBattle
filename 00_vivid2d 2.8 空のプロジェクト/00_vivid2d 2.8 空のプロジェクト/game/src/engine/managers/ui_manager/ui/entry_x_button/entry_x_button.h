#pragma once

#include "vivid.h"
#include "..\ui.h"
class CEntryXButton : public CUI
{
public:
    enum class STATE
    {
        WAIT,
        FADE_IN,
        FADE_OUT,
    };
    /*!
     *  @brief      コンストラクタ
     */
    CEntryXButton(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CEntryXButton(void);

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

private:
    static const vivid::Vector2     m_position;     //!< 位置
    static const int                m_height;       //!< 高さ
    static const int                m_width;        //!< 幅
    static const vivid::Rect        m_rect;         //!< 読み込み範囲
    static const vivid::Vector2     m_anchor;       //!< 基準点
    static const vivid::Vector2     m_scale;        //!< 拡縮
    static const float              m_wait_time;    //!< 待機時間
    static const int                m_fade_speed;   //!< フェードスピード

    unsigned int                    m_Color[2];     //!< RGBA(アルファ値切り替え用)    
    int                             m_FadeSpeed;    //!< フェードスピード
    int                             m_UINum;        //!< 表示するUIの番号
    CTimer                          m_WaitTimer;    //!< 待機させるタイマー
    STATE                           m_State;        //!< 状態
};
