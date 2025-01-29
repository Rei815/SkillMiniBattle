#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include "../../../stage/stage.h"
#include "../../../sound_manager/sound_manager.h"

class CResultGame : public IScene
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CResultGame(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CResultGame(void);

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
    BGM_ID          m_Sound;                //
};
