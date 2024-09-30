
/*!
 *  @file       sound_manager.cpp
 *  @brief      サウンド管理
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "sound_manager.h"

const char* CSoundManager::m_sound_file_names[] =
{
    "data\\Audios\\bgm.wav",
    "data\\Audios\\shot.wav",
    "data\\Audios\\homing_shot.wav",
    "data\\Audios\\destory.wav",
    "data\\Audios\\boss_destory.wav",
    "data\\Audios\\player_hit.wav",
    "data\\Audios\\warning.wav",
    "data\\Audios\\warning_short.wav",
    "data\\Audios\\gameover.wav",
    "data\\Audios\\gameclear.wav",
};

/*
 *  インスタンスの取得
 */
CSoundManager&
CSoundManager::GetInstance(void)
{
    static CSoundManager instance;

    return instance;
}

/*
 *  読み込み
 */
void
CSoundManager::Load(void)
{
    for (int i = 0; i < (int)SOUND_ID::MAX; ++i)
        vivid::LoadSound(m_sound_file_names[i]);
}

/*
 *  再生
 */
void
CSoundManager::Play(SOUND_ID id, bool loop)
{
    vivid::PlaySound(m_sound_file_names[(int)id], loop);
}

/*
 *  コンストラクタ
 */
CSoundManager::CSoundManager(void)
{
}

/*
 *  コピーコンストラクタ
 */
CSoundManager::CSoundManager(const CSoundManager& rhs)
{
    (void)rhs;
}

/*
 *  デストラクタ
 */
CSoundManager::~CSoundManager(void)
{
}

/*
 *  代入演算子
 */
CSoundManager&
CSoundManager::operator=(const CSoundManager& rhs)
{
    (void)rhs;

    return *this;
}
