#pragma once

#include "..\game.h"

class CDaruma_FallDownGame : public CGame
{
public:

    /*!
     *  @brief      コンストラクタ
     */
    CDaruma_FallDownGame(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CDaruma_FallDownGame(void);

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

};
