#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../object_manager/object/fall_object/mark_id.h"
class CFallOutTopic : public CUI
{
public:
    enum class STATE
    {
        WAIT,   //!< 何もしない
        SWITCHING, //!< 絵が切り替わり続けている状態
        PICK_UP  //!< 絵が決まった状態
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
    static const vivid::Vector2     m_adjustPosition;   //!< 背景との調整値
    static const float              m_speed;            //!< 動きの速度
    static const float              m_change_time;      //!< 切り替わる時間
    static const float              m_wait_time;        //!< 待機時間

    float                           m_Time;
    std::string                     m_FileName;
    vivid::Rect                     m_Rect;
    CTimer                          m_Timer;
    CTimer                          m_SelectTimer;      //!< お題が決まるまでの時間
    CTimer                          m_StopTimer;
    MARK_ID                         m_PreviousID;       //!< 前回のID
    MARK_ID                         m_CurrentID;        //!< 今回のID

    STATE                           m_State;
};
