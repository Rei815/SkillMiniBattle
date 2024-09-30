
/*!
 *  @file       sound_manager.cpp
 *  @brief      �T�E���h�Ǘ�
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
 *  �C���X�^���X�̎擾
 */
CSoundManager&
CSoundManager::GetInstance(void)
{
    static CSoundManager instance;

    return instance;
}

/*
 *  �ǂݍ���
 */
void
CSoundManager::Load(void)
{
    for (int i = 0; i < (int)SOUND_ID::MAX; ++i)
        vivid::LoadSound(m_sound_file_names[i]);
}

/*
 *  �Đ�
 */
void
CSoundManager::Play(SOUND_ID id, bool loop)
{
    vivid::PlaySound(m_sound_file_names[(int)id], loop);
}

/*
 *  �R���X�g���N�^
 */
CSoundManager::CSoundManager(void)
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
CSoundManager::CSoundManager(const CSoundManager& rhs)
{
    (void)rhs;
}

/*
 *  �f�X�g���N�^
 */
CSoundManager::~CSoundManager(void)
{
}

/*
 *  ������Z�q
 */
CSoundManager&
CSoundManager::operator=(const CSoundManager& rhs)
{
    (void)rhs;

    return *this;
}
