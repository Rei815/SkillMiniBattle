#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include "../../../ui_manager/ui/scene_ui_parent/scene_ui_parent.h"
#include "../../../ui_manager/ui/plane_game_image/plane_game_image.h"


class CGameRollAndReveal
    : public IScene
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CGameRollAndReveal(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CGameRollAndReveal(void);

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
    static const int                    m_games_num;            //!< ゲーム数
    static const CVector3               m_camera_position;      //!< カメラの位置
    static const float                  m_circle_radius;        //!< 円の半径
    CSceneUIParent*                     m_PlaneUIParent;        //!< UIの親(回転プレーン)
    CSceneUIParent*                     m_RevealUIParent;       //!< UIの親(説明用UI)
    CPlaneGameImage*                    m_SelectedPlane;        //!< 平面のゲーム画像
    bool                                m_SelectedGameFlag;     //!< ゲームが選ばれたか
    bool                                m_GameInfomationFlag;   //!< ゲームの説明が出たか
    GAME_ID                             m_SelectedGameID;       //!< 選ばれたゲームのID
};
