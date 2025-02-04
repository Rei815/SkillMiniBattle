#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include "../../../ui_manager/ui/scene_ui_parent/scene_ui_parent.h"
#include "../../../ui_manager/ui/plane_game_image/plane_game_image.h"


class CSelectGame
    : public IScene
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CSelectGame(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CSelectGame(void);

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
    static const int    m_games_num;
    static const float  m_circle_radius;
    CSceneUIParent*     m_FirstSceneUIParent;
    CSceneUIParent*     m_SecondSceneUIParent;
    CPlaneGameImage*    m_planeGameImage;
    bool                m_SelectedGameFlag;
    bool                m_GameInfomationFlag;
    GAME_ID             m_SelectedGameID;
};
