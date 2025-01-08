#pragma once

#include "..\game.h"
#include "..\..\..\..\ui_manager\ui\ui_id.h"
#include "../../../../ui_manager/ui/fallout_topic/fallout_topic.h"
class CFallGame : public CGame
{
public:

    /*!
     *  @brief      コンストラクタ
     */
    CFallGame(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CFallGame(void);

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

    struct FALL_INFO
    {
        IObject*    object;
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
     *  @brief      終了
     */
    void    Finish(void);

    /*!
     *  @brief      終了判定
     */
    void    CheckFinish(void) override;

    /*!
     *  @brief      落ちるオブジェクトの選択
     * 
     *  @return     オブジェクトID
     */
    FALL_INFO    ChooseObject(void);

    static const CTransform         m_object_transform_list[];  //!< 落ちるオブジェクトのトランスフォーム
    static const float              m_time_accelerator;         //!< 落ちるまでの速度を増やす
    static const float              m_min_time;                 //!< 落ちるまでの最小時間
    static const float              m_fall_time;             //!< 落ちるまでの初期時間
    static const float              m_object_delay_time;        //!< 再抽選までの時間
    static const float              m_add_topic_time;           //!< お題が増えるまでの時間
    static const float              m_reset_topic_time;           //!< リセットまでの待機時間
    static const float              m_defeat_height;            //!< 負ける高さ
    static const CVector3           m_camera_position;          //!< カメラの位置
    static const CVector3           m_camera_direction;         //!< カメラの方向
    static const vivid::Vector2     m_topic_positionList[];     //!< お題位置
    static const int                m_max_topic_num;            //!< お題数
    float                           m_FallTime;                 //!< 落ちるまでの時間
    CTimer                          m_ChooseObjectTimer[5];     //!< 抽選タイマー
    CTimer                          m_AddTopicTimer;            //!< お題が増えるタイマー
    CTimer                          m_ResetTopicTimer;          //!< お題リセットタイマー
    IObject*                        m_Object;                   //!< オブジェクト

    using TOPIC_LIST = std::list<CFallOutTopic*>;

    TOPIC_LIST                      m_TopicList;                //!< お題のリスト
};
