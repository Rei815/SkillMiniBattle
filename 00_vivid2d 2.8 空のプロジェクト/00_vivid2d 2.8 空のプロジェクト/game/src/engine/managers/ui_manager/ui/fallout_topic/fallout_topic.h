#pragma once

#include "vivid.h"
#include "..\ui.h"
#include <memory>
#include "../../../../utility/timer/timer.h"

/*!
 *  @brief      マークID
 */
enum class MARK_ID
{
    CIRCLE,     //!< 丸マーク
    CROSS,      //!< バツマーク
    MOON,       //!< 月マーク
    SQUARE,     //!< 四角マーク
    SUN,        //!< 太陽マーク
    TRIANGLE,   //!< 三角マーク
    NONE,
};
class CFallOutTopic : public CUI
{
public:
    enum class STATE
    {
        APPEAR,     //!< 出現
        WAIT,       //!< 何もしない
        SWITCHING,  //!< 絵が切り替わり続けている状態
        PICK_UP,    //!< 絵が決まった状態
        FINISH      //!< ゲーム終了時の状態
    };

    /*!
     *  @brief      コンストラクタ
     */
    CFallOutTopic(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CFallOutTopic(void);

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

    void        SetMarkID(MARK_ID markID);

    void        SetTimer(float time);

    STATE       GetState();

    void        SetState(CFallOutTopic::STATE state);
private:
    static const std::string        m_file_name;        //!< ファイル名
    static const int                m_height;           //!< 高さ
    static const int                m_width;            //!< 幅
    static const vivid::Rect        m_rect;             //!< 読み込み範囲
    static const vivid::Vector2     m_anchor;           //!< 基準点
    static const vivid::Vector2     m_scale;            //!< 拡縮
    static const vivid::Vector2     m_adjust_position;  //!< 背景との調整値
    static const float              m_speed;            //!< 動きの速度
    static const float              m_change_time;      //!< 切り替わる時間
    static const float              m_wait_time;        //!< 待機時間
    static const float              m_end_y;            //!< 出現時の停止する高さ
    static const float              m_end_time;         //!< 終了時間
    float                           m_EaseTimer;        //!< 開始時間
    float                           m_StartValue;       //!< 開始値
    float                           m_FinishValue;      //!< 終了値
    float                           m_Time;
    std::string                     m_FileName;
    vivid::Rect                     m_Rect;
    CTimer                          m_Timer;
    CTimer                          m_SelectTimer;      //!< お題が決まるまでの時間
    CTimer                          m_StopTimer;
    MARK_ID                         m_CurrentID;        //!< 今回のID

    STATE                           m_State;
    std::shared_ptr<CUI>            m_BackGround;

};
