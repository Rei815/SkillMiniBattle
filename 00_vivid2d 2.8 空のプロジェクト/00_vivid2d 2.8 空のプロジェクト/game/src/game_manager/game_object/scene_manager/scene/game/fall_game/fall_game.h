#pragma once

#include "..\game.h"
#include "..\..\..\..\ui_manager\ui\ui_id.h"
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

    struct FALL_INFO
    {
        OBJECT_ID   objectID = OBJECT_ID::NONE;
        UI_ID       uiID = UI_ID::NONE;
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
     *  @brief      落ちるオブジェクトの選択
     * 
     *  @return     オブジェクトID
     */
    FALL_INFO    ChooseObject(void);

    static const CTransform         m_object_transform_list[];
    float                           m_FallTime;

    CTimer                          m_Timer;


};
