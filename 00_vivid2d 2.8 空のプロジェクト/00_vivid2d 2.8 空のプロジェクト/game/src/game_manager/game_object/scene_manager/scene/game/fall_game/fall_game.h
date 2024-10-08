#pragma once

#include "..\game.h"

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

    int     m_FallTime;
    int     m_FallTimer;

    static const CVector3 m_object_position_list[];
};
