
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



const char* CSoundManager::m_bgm_file_names[] =
{
    "data\\Audios\\BGM\\Main_BGM.mp3",
    "data\\Audios\\BGM\\Result_BGM.mp3",
    "data\\Audios\\BGM\\Ready_BGM.mp3",
};

const char* CSoundManager::m_se_file_names[] =
{
    "data\\Audios\\SE\\Barrier_SE.mp3",
    "data\\Audios\\SE\\CancelButton_SE.mp3",
    "data\\Audios\\SE\\CannonShot_SE.mp3",
    "data\\Audios\\SE\\Dash_SE.mp3",
    "data\\Audios\\SE\\DecideButton_SE.mp3",
    "data\\Audios\\SE\\FallOutDecide_SE.mp3",
    "data\\Audios\\SE\\FallOutRaffle_SE.mp3",
    "data\\Audios\\SE\\Floating_SE.mp3",
    "data\\Audios\\SE\\GameDecide_SE.mp3",
    "data\\Audios\\SE\\GameFinish_SE.mp3",
    "data\\Audios\\SE\\GameRaffle_SE.mp3",
    "data\\Audios\\SE\\GameStart_SE.mp3",
    "data\\Audios\\SE\\GravityArea_SE.mp3",
    "data\\Audios\\SE\\HideTopic_SE.mp3",
    "data\\Audios\\SE\\Invisible_SE.mp3",
    "data\\Audios\\SE\\KeyGet_SE.mp3",
    "data\\Audios\\SE\\Mimicry_SE.mp3",
    "data\\Audios\\SE\\Resurect_SE.mp3",
    "data\\Audios\\SE\\SceneMove_SE.mp3",
    "data\\Audios\\SE\\Select_SE.mp3",
    "data\\Audios\\SE\\Skill_SE.mp3",
    "data\\Audios\\SE\\Slow_SE.mp3",
    "data\\Audios\\SE\\SpawnWall_SE.mp3",
    "data\\Audios\\SE\\Stomp_SE.mp3",
    "data\\Audios\\SE\\StrongWindow_SE.mp3",
    "data\\Audios\\SE\\Stun_SE.mp3",
    "data\\Audios\\SE\\Reflection_SE.mp3",
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
CSoundManager::Load_BGM(void)
{
    for (int i = 0; i < (int)BGM_ID::MAX; ++i)
        vivid::LoadSound(m_bgm_file_names[i]);
}

void
CSoundManager::Load_SE(void)
{
    for (int i = 0; i < (int)SE_ID::MAX; ++i)
        vivid::LoadSound(m_se_file_names[i]);
}

/*
 *  �Đ�
 */
void
CSoundManager::Play_BGM(BGM_ID id, bool loop)
{
    vivid::PlaySound(m_bgm_file_names[(int)id], loop);
}

void
CSoundManager::Play_SE(SE_ID id,bool loop)
{
    vivid::PlaySound(m_se_file_names[(int)id],false);
}

/*
 *��~
 */
void
CSoundManager::Stop_BGM(BGM_ID id)
{
    vivid::StopSound(m_bgm_file_names[(int)id]);
}


void
CSoundManager::Stop_SE(SE_ID id)
{
    vivid::StopSound(m_se_file_names[(int)id]);
}

/*
 *  ����
 */
void CSoundManager::SetBGMVolume(BGM_ID id, int volume)
{
    vivid::SetSoundVolume(m_bgm_file_names[(int)id], volume);
}

void CSoundManager::SetSEVolume(SE_ID id, int volume)
{
    vivid::SetSoundVolume(m_se_file_names[(int)id], volume);

}


void CSoundManager::Finalize(void)
{
    for (int i = 0; i < (int)SE_ID::MAX; i++)
    {
        vivid::StopSound(m_se_file_names[i]);
    }
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
