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
    void Initialize(SCENE_ID scene_id);

    /*!
     *  @brief      更新
     */
    void        Update(void);

    /*!
     *  @brief      描画
     */
    void        Draw(void);

};
