#pragma once

#include "..\game.h"

class CDodgeBallGame : public CGame
{
public:

    /*!
     *  @brief      コンストラクタ
     */
    CDodgeBallGame(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CDodgeBallGame(void);

    /*!
     *  @brief      初期化
     */
    void Initialize(void);

};
