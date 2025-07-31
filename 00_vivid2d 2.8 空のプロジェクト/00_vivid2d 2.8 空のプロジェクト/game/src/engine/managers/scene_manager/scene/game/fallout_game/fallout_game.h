#pragma once

#include "..\game.h"
#include "..\..\..\..\ui_manager\ui\ui_id.h"
#include "../../../../ui_manager/ui/fallout_topic/fallout_topic.h"
#include <memory>
#include <array>
#include <random>
class CFallOutGame : public CGame
{
public:

    /*!
     *  @brief      コンストラクタ
     */
    CFallOutGame(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CFallOutGame(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(SCENE_ID scene_id);

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

    //落ちる床のポインタとマーク
    struct FALL_OBJECT＿INFO
    {
        std::shared_ptr<CGameObject>    object;
        MARK_ID     markID = MARK_ID::CIRCLE;
    };

    /*!
     *  @brief      スタート
     */
    void    Start(void);

    /*!
     *  @brief      プレイ
     */
    void    Play(void);

    /*!
     *  @brief      お題の選択
     */
    void    ChooseTopic(void);

    /*!
     *  @brief      お題のリセット
     */
    void    ResetTopic(void);

    /*!
     *  @brief      お題の追加
     */
    void    AddTopic(void);

    /*!
     *  @brief      落ちるオブジェクトの選択
     * 
     *  @return     オブジェクトID
     */
    FALL_OBJECT＿INFO    ChooseObject(void);

    /*!
     *  @brief      終了
     */
    void    Finish(void);

    /*!
     *  @brief      終了判定
     */
    void    CheckFinish(void) override;

    /*!
     *  @brief      お題の終了処理
     */
    void    FinishTopic(void);

    static const CTransform             m_floor_transform_list[];   //!< 落ちる床のトランスフォーム
    static const float                  m_player_spawn_height;      //!< プレイヤーが出現する高さ
    static const float                  m_time_accelerator;         //!< 落ちるまでの速度を増やす
    static const float                  m_min_time;                 //!< 落ちるまでの最小時間
    static const float                  m_fall_time;                //!< 落ちるまでの初期時間
    static const float                  m_object_delay_time;        //!< 再抽選までの時間
    static const float                  m_topic_interval_time;      //!< 抽選の感覚
    static const float                  m_add_topic_time;           //!< お題が増えるまでの時間
    static const float                  m_reset_topic_time;         //!< リセットまでの待機時間
    static const float                  m_defeat_height;            //!< 負ける高さ
    static const float                  m_extend_return_time;       //!< 床の復活が延びるまでの時間
    static const CVector3               m_camera_position;          //!< カメラの位置
    static const CVector3               m_camera_direction;         //!< カメラの方向
    static const vivid::Vector2         m_topic_positionList[];     //!< お題位置
    static constexpr int                m_max_topic_num = 5;        //!< お題数(5)
    static const CVector3               m_player_default_forward;   //!< プレイヤーのスポーン時の正面方向
    float                               m_FallTime;                 //!< 落ちるまでの時間
    std::array<CTimer,m_max_topic_num>  m_ChooseObjectTimer;        //!< 抽選タイマー
    CTimer                              m_AddTopicTimer;            //!< お題が増えるタイマー
    CTimer                              m_ResetTopicTimer;          //!< お題リセットタイマー
    CTimer                              m_ExtendTimer;              //!< 床の復活が延びるまでのタイマー

    using TOPIC_LIST = std::list<std::shared_ptr<CFallOutTopic>>;

    TOPIC_LIST                          m_TopicList;                //!< お題のリスト
};
