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
    /*!
     *  @brief      ボタンの長押しをチェック
     */
    void CheckButtonHold(void);
    /*!
     *  @brief      ボタンの押下をチェック
     */
    void CheckButtonDown(void);
    /*!
     *  @brief      ボタンを離したかチェック
     */
    void CheckButtonUp(void);

    static const CVector3   m_spawn_position;       //生成位置
    static const float      m_respawn_height;       //リスポーンさせる高さ
    static const float      m_start_time;           //開始までの時間
    static const float      m_hold_start_time;      //長押しで開始する秒数
    static const float      m_exit_time;            //退室までに必要な秒数
    static const CVector3   m_camera_position;      //カメラの位置
    static const CVector3   m_camera_direction;     //カメラの向き
    UNIT_ID                 m_UnitID;               //次に生成するプレイヤーのID
    UNIT_ID                 m_PlayerArray[4];       //存在しているプレイヤーのID
    CTimer                  m_GameStartTimer;       //ゲーム開始までのタイマー
    CTimer                  m_HoldStartTimer;       //長押しで開始するタイマー
    CTimer                  m_HoldTimer[4];         //長押ししている時間
    bool                    m_WasPressdThisFrame;   //同フレーム中の押下フラグ
    bool                    m_WasPressd;            //押下フラグ
    int                     m_PlayerNum;
};
