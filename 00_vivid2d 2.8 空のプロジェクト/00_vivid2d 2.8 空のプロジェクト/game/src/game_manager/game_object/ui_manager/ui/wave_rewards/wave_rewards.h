#pragma once

#include "vivid.h"
#include "..\..\..\..\..\utility\utility.h"
#include "..\ui.h"
#include "reward_id.h"
#include "reward/reward.h"
class CWaveRewards : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CWaveRewards();

    /*!
     *  @brief      デストラクタ
     */
    ~CWaveRewards(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(void);

    /*!
     *  @brief      更新
     */
    void        Update();

    /*!
     *  @brief      描画
     */
    void        Draw();

    /*!
     *  @brief      解放
     */
    void        Finalize(void);

protected:

    void        EaseOut(void);
    static const vivid::Vector2     m_position;         //!< 位置
    static const int                m_height;           //!< 高さ
    static const int                m_width;            //!< 幅
    static const float              m_offset;           //!< 報酬同士の距離
    static const float              m_end_time;         //!< 終了時間
    static const float              m_end_x;           //!< 終了値

    float                           m_StartTime;        //!< 開始時間
    float                           m_StartValue;       //!< 開始値
    float                           m_FinishValue;      //!< 終了値
    CEasing                         m_Easing;           //!< イージング


    /*!
     *  @brief      REWARDリスト型
     */
    using REWARD_LIST = std::vector<CReward*>;

    REWARD_LIST         m_RewardList;               //!< 報酬リスト

    static const int    m_max_reward_num = 3;
    CReward*            m_Rewards[m_max_reward_num];     //!< 報酬リストから選ばれた報酬

    int                 m_Num;
    int                 m_Nums[m_max_reward_num];
};
