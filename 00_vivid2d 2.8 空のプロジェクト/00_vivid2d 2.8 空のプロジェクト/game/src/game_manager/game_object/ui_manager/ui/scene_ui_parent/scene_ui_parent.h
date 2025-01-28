#pragma once

#include "vivid.h"
#include "..\ui.h"

class  CSceneUIParent : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CSceneUIParent(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CSceneUIParent(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize();

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

    static const vivid::Vector2             m_position;             //!< 位置
    static const int            m_speed;                //!< 移動速度
    static const float			m_down_final_height;	//!< 降りるときの最終高度

    static const float          m_end_time;             //!< 終了時間
    float                       m_EaseTimer;            //!< 経過時間
    float                       m_StartValue;           //!< 開始値
    float                       m_FinishValue;          //!< 終了値

};