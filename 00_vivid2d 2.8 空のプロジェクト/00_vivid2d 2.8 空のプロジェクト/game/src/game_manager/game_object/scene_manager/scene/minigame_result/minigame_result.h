#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include "../../../ui_manager/ui/scene_ui_parent/scene_ui_parent.h"

class CMiniGameResult
    : public IScene
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CMiniGameResult(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CMiniGameResult(void);

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
    static const vivid::Vector2 m_origin_key_pos;
    static const vivid::Vector2 m_origin_icon_pos;
    static const vivid::Vector2 m_origin_notice_pos;
    static const float          m_key_offset;           //鍵同士の距離
    static const float          m_icon_offset;          //アイコン同士の距離
    static const float          m_notice_offset;        //張り紙同士の距離
    static const float          m_players_key_offset;   //プレイヤー間の鍵の距離
    static const vivid::Vector2 m_notice_scale;         //張り紙の大きさ
    CSceneUIParent*             m_SceneUIParent;

};
