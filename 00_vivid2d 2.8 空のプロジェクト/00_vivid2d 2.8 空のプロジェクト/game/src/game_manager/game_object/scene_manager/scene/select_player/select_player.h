#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"

class CSelectPlayer
    : public IScene
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CSelectPlayer(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CSelectPlayer(void);

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
};
