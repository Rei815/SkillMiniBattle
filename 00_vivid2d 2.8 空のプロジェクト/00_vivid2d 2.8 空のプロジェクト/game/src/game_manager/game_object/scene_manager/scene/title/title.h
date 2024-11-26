#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include "../../../stage/stage.h"

class CTitle
    : public IScene
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CTitle(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CTitle(void);

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
    /*!
     *  @brief  状態ID
     */
    enum class STATE
    {
        WAIT,
    };

    STATE           m_State;                //!< 状態ID
};
