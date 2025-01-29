
/*!
 *  @file       game_manager.cpp
 *  @brief      ゲーム管理
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "game_manager.h"
#include "game_object\game_object.h"

 /*
  *  インスタンスの取得
  */
CGameManager&
CGameManager::GetInstance(void)
{
    static CGameManager instance;

    return instance;
}

/*
 *  初期化
 */
void
CGameManager::Initialize(void)
{
    // モデルマネージャー取得
    CModelManager& model = CModelManager::GetInstance();

    // モデル読み込み
    model.Load();

    // サウンドマネージャー取得
    CSoundManager& sound = CSoundManager::GetInstance();

    // サウンド読み込み
    sound.Load_SE();
    sound.Load_BGM();

    // BGM再生
    //sound.Play(SOUND_ID::BGM, true);

    // シーンマネージャー初期化
    CSceneManager::GetInstance().Initialize();
}

/*
 *  更新
 */
void
CGameManager::Update(void)
{

    // シーンマネージャー更新
    CSceneManager::GetInstance().Update();
}

/*
 *  描画
 */
void
CGameManager::Draw(void)
{
    // シーンマネージャー描画
    CSceneManager::GetInstance().Draw();
    CSceneManager::GetInstance().DrawSceneEffect();
}

/*
 *  解放
 */
void
CGameManager::Finalize(void)
{
    // シーンマネージャー解放
    CSceneManager::GetInstance().Finalize();
}

/*
 *  コンストラクタ
 */
CGameManager::CGameManager(void)
{
}

/*
 *  コピーコンストラクタ
 */
CGameManager::CGameManager(const CGameManager& rhs)
{
    (void)rhs;
}

/*
 *  デストラクタ
 */
CGameManager::~CGameManager(void)
{
}

/*
 *  代入演算子
 */
CGameManager&
CGameManager::operator=(const CGameManager& rhs)
{
    (void)rhs;

    return *this;
}
