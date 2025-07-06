#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../../utility/timer/timer.h"

class CStartGameCount : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CStartGameCount(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CStartGameCount(void);

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
    enum class START_COUNT_MOVE
    {
        MOVE_IN,
        STOP,
        MOVE_OUT,
    };

    static const int                m_height;           //!< 高さ
    static const int                m_width;            //!< 幅
    static const vivid::Rect        m_rect;             //!< 読み込み範囲
    static const vivid::Vector2     m_anchor;           //!< 基準点
    static const vivid::Vector2     m_default_scale;    //!< 拡縮
    static const vivid::Vector2     m_max_scale;        //!< 最大の拡大率

    static const std::string        m_file_name[];      //!< カウントダウンのファイル名

    static const float              m_movein_time;
    static const float              m_stop_time;
    static const float              m_moveout_time;

    static const vivid::Vector2     m_movein_position;      //!< 生成時の座標
    static const float              m_stop_position_y;      //!< 停止する時のy座標
    static const float              m_moveout_position_y;   //!< 消滅時のy座標

    START_COUNT_MOVE                m_MoveState;
    CTimer                          m_Timer;
    int                             m_CountDown;
};
