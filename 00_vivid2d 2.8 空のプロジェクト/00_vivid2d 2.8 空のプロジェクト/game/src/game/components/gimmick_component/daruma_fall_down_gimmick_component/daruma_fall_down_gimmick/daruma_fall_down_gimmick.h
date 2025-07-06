#pragma once
#include "../../../../../engine/core/game_object/game_object.h"
enum class OGRE_STATE
{
    READY,
    PLAY,
    WAIT,
    FINISH,
};

enum class TURN_TYPE
{
    FEINT,
    SLOW,
    FAST,

    TYPE_NUM,
};

class CDarumaFallDownGimmick
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     */
    CDarumaFallDownGimmick();

    /*!
     *  @brief      デストラクタ
     */
    ~CDarumaFallDownGimmick(void);

    /*!
     *  @brief      初期化
     *
     */
    void    Initialize(CGameObject* object);

    /*!
     *  @brief      更新
     */
    void    Update(void);

    /*!
     *  @brief      描画
     */
    void    Draw(void);

    /*!
     *  @brief      解放
     */
    void    Finalize(void);

    /*!
    *  @brief      準備
    */
    virtual void    Ready(void);

    /*!
    *  @brief      プレイ
    */
    virtual void    Play(void);

    /*!
    *  @brief      待機
    */
    virtual void    Wait(void);

    /*!
    *  @brief      終了
    */
    virtual void    Finish(void);

    /*!
    *  @brief      振り向きフェイント
    */
    virtual void    Feint(void);

    virtual void    OgreControlTurn(void);

private:

    static const float      m_default_ready_time;   //デフォルトの鬼の準備時間
    static const float      m_default_wait_time;    //                待機時間
    static const float      m_default_turn_angle;   //                振り向き角度

    static const float      m_feint_ready_time;     //フェイントの鬼の準備時間
    static const float      m_feint_wait_time;      //                待機時間
    static const float      m_feint_turn_angle;     //                振り向き角度

    static const float      m_turn_speed;            //鬼の振り向く速度

    float                   m_ReadyTime;                          //鬼が振り向くまでの時間
    float                   m_WaitTime;                           //鬼の待機時間
    float                   m_TurnAngle;                          //振り向く角度
    int                     m_RestPlayer;                         //残りのプレイヤー数

    OGRE_STATE              m_OgreState;                     //鬼の状態
    TURN_TYPE               m_TurnType;                      //振り向きの種類
    CTransform              m_Transform;                     //鬼のトランスフォーム
    CTimer                  m_Timer;                         //タイマー
    CGameObject* m_Object;

};
