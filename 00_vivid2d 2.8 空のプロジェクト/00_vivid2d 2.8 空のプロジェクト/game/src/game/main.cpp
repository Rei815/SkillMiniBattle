
/*!
 *  @file       main.cpp
 *  @brief      エントリーポイント
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "vivid.h"
#include "game_manager/game_manager.h"

 /*!
  *  @brief      描画関数
  */
void
Display(void)
{
    CGameManager& game = CGameManager::GetInstance();

    // ゲームマネージャー更新
    game.Update();

    // ゲームマネージャー描画
    game.Draw();

}

/*!
 *  @brief      メイン関数
 *
 *  @param[in]  hInst       インスタンスハンドル
 *  @param[in]  hPrevInst   Win16時代の遺物
 *  @param[in]  lpCmdLine   コマンドライン文字列
 *  @param[in]  nCmdShow    ウィンドの表示方法
 *
 *  @return     メイン関数の成否
 */
int WINAPI
WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrevInst, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    (void)hPrevInst;
    (void)lpCmdLine;
    (void)nCmdShow;

    // vividライブラリ初期化
    vivid::Initialize(hInst);

    // ゲームマネージャー初期化
    CGameManager::GetInstance().Initialize();


    // 更新/描画関数登録
    vivid::DisplayFunction(Display);

    // ゲームループ
    vivid::MainLoop();

    // ゲームマネージャー解放
    CGameManager::GetInstance().Finalize();

    // vividライブラリ解放
    vivid::Finalize();
}
