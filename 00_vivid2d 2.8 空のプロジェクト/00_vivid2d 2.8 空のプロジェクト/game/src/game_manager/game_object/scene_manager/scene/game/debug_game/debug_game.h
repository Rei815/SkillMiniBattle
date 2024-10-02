#pragma once

#include "..\game.h"

class CDebugGame : public CGame
{
public:

    /*!
     *  @brief      コンストラクタ
     */
    CDebugGame(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CDebugGame(void);

    /*!
     *  @brief      初期化
     */
    void Initialize(void);

};
