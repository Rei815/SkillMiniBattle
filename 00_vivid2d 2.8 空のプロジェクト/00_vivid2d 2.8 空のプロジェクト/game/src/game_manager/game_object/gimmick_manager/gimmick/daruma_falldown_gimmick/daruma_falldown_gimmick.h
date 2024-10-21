
#pragma once
#include "..\gimmick.h"

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
    void    Initialize();

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

private:

    bool m_TurnAround;           //鬼が振り向いたかどうか
    bool m_SeenMove;             //鬼に見られてる時に動いたか
    bool m_Touch;                //鬼に触ったかどうか
    bool m_GameEnd;              //ゲーム終了条件を満たしたか

    float m_TurnAroundTime;      //鬼が振り向くまでの時間
    int   m_RestPlayer;          //残りのプレイヤー数

    CTimer  m_Timer;
};
