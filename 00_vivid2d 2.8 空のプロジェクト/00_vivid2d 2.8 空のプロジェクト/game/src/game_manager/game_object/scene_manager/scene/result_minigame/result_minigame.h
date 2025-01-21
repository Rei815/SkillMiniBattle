#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include "../../../stage/stage.h"

class CResultMiniGame
    : public IScene
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CResultMiniGame(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CResultMiniGame(void);

    /*!
     *  @brief      初期化
     */
    void Initialize(SCENE_ID scene_id);

    /*!
     *  @brief      更新
     */
    void Update(void);

    /*!
     *  @brief      描画
     */
    void Draw(void);

    /*!
     *  @brief      解放
     */
    void Finalize(void);

private:
    static const vivid::Vector2 m_OriginKeyPos;
    static const float          m_key_offset;        //鍵と鍵の距離
    static const float          m_players_key_offset;  //プレイヤー間の鍵の距離
};
