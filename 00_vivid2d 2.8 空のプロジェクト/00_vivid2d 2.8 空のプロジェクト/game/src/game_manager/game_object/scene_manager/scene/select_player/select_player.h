#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include "..\..\..\ui_manager\ui\player_num_select\player_num_select.h"

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
    static const vivid::Vector2 m_player_num_ui_pos[(int)UNIT_ID::NONE];
    static const float          m_player_num_ui_scale;

    CPlayerNumSelect* m_PlayerNumUI[(int)UNIT_ID::NONE];
};
