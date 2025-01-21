#pragma once

#include "vivid.h"
#include "..\ui.h"
class CFade : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CFade(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CFade(void);

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
    static const std::string        m_file_name;        //!< ファイル名

    static const vivid::Vector2     m_position;     //!< 位置
    static const int                m_height;       //!< 高さ
    static const int                m_width;        //!< 幅
    static const float              m_wait_time;    //!< アルファ値が最大になった時の待機時間
    unsigned int                    m_Color;
    static const int                m_fade_speed;
    int                             m_FadeSpeed;
    CTimer                          m_Timer;
};