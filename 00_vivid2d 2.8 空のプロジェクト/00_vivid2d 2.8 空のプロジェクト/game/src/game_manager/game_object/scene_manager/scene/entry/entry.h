#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include <list>
#include "..\..\..\controller_manager\controller\controller.h"
class CEntry : public IScene
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CEntry(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CEntry(void);

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
    std::list<CController*> m_PlayerControllerList;
};
