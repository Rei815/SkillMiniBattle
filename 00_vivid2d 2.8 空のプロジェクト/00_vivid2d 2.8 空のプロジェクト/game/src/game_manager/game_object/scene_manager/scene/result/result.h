#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include "../../../stage/stage.h"

class CResult
    : public IScene
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CResult(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CResult(void);

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
    static const float          m_KeyOffset;
};
