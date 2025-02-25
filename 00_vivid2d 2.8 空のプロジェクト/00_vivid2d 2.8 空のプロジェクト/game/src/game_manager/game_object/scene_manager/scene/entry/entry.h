#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include <list>
#include "..\..\..\controller_manager\controller\controller.h"
#include "..\..\..\unit_manager\unit\unit_id.h"
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
    static const CVector3   m_spawn_position;
    static const float      m_respawn_height;
    static const float      m_start_time;
    static const CVector3   m_camera_position;
    static const CVector3   m_camera_direction;
    UNIT_ID                 m_UnitID;
    UNIT_ID                 m_PlayerArray[4];
    CTimer                  m_StartTimer;
};
