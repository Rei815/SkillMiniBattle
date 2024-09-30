#pragma once

#include "vivid.h"
#include "..\..\..\..\..\utility\utility.h"
#include "..\ui.h"

class CWaveClear : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CWaveClear(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CWaveClear(void);

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
     *  @brief      中心位置取得
     */
    vivid::Vector2        GetCenterPosition(void);


private:

    void        EaseOut(void);
    void        EaseIn(void);
    void        Reset(void);
    static const vivid::Vector2     m_position;         //!< 位置
    static const int                m_height;           //!< 高さ
    static const int                m_width;            //!< 幅
    static const vivid::Rect        m_rect;             //!< 読み込み範囲
    static const vivid::Vector2     m_anchor;           //!< 基準点
    static const vivid::Vector2     m_scale;            //!< 拡縮
    static const float              m_end_time;         //!< 終了時間
    static const float              m_relay_x;         //!< 中継値
    static const float              m_end_x;           //!< 終了値

    float                           m_StartTime;        //!< 開始時間
    float                           m_StartValue;       //!< 開始値
    float                           m_FinishValue;      //!< 終了値
    CEasing                         m_Easing;           //!< イージング
};
