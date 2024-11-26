
#pragma once
#include "..\gimmick.h"

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

class CDaruma_FallDownGimmick : public CGimmick
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     */
    CDaruma_FallDownGimmick();

    /*!
     *  @brief      デストラクタ
     */
    ~CDaruma_FallDownGimmick(void);

    /*!
     *  @brief      初期化
     *
     */
    void    Initialize(IObject* object);

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

    /*!
    *  @brief      振り向き早い
    */
    virtual void    Fast(void);

    /*!
    *  @brief      振り向き遅い
    */
    virtual void    Slow(void);

private:

    OGRE_STATE m_OgreState;
    TURN_TYPE  m_TurnType;

    bool m_GameEnd;              //ゲーム終了条件を満たしたか

    float m_ReadyTime;      //鬼が振り向くまでの時間
    float m_WaitTime;            //鬼の待機時間
    float m_TurnSpeed;           //鬼の振り向く速度
    float m_TurnAngle;           //振り向く角度
    int   m_RestPlayer;          //残りのプレイヤー数

    CTransform m_Transform;      //鬼のトランスフォーム
    CTimer  m_Timer;
};
