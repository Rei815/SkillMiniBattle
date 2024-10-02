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
    void Initialize(void);

};
