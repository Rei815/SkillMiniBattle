#pragma once

#include "vivid.h"
#include "..\ui.h"

class CStartGameText : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CStartGameText(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CStartGameText(void);

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
    enum class START_TEXT_MOVE
    {
        ZOOM_IN,
        STOP,
        FADE_OUT,
    };

    static const int                m_height;           //!< 高さ
    static const int                m_width;            //!< 幅
    static const vivid::Rect        m_rect;             //!< 読み込み範囲
    static const vivid::Vector2     m_anchor;           //!< 基準点
    static const vivid::Vector2     m_default_scale;    //!< 生成時の拡縮
    static const vivid::Vector2     m_max_scale;        //!< 最大の拡大率
    static const vivid::Vector2     m_default_position; //!< 生成時の座標
    static const unsigned int       m_default_color;    //!< 生成時の色

    static const std::string        m_file_name;      //!< カウントダウンのファイル名

    static const float              m_zoomin_time;
    static const float              m_stop_time;
    static const float              m_fadeout_time;


    vivid::Vector2                  m_Scale;
    START_TEXT_MOVE                 m_MoveState;
    CTimer                          m_Timer;
    unsigned int                    m_Color;
};
