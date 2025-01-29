
/*!
 *  @file       game_manager.cpp
 *  @brief      �Q�[���Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "game_manager.h"
#include "game_object\game_object.h"

 /*
  *  �C���X�^���X�̎擾
  */
CGameManager&
CGameManager::GetInstance(void)
{
    static CGameManager instance;

    return instance;
}

/*
 *  ������
 */
void
CGameManager::Initialize(void)
{
    // ���f���}�l�[�W���[�擾
    CModelManager& model = CModelManager::GetInstance();

    // ���f���ǂݍ���
    model.Load();

    // �T�E���h�}�l�[�W���[�擾
    CSoundManager& sound = CSoundManager::GetInstance();

    // �T�E���h�ǂݍ���
    sound.Load_SE();
    sound.Load_BGM();

    // BGM�Đ�
    //sound.Play(SOUND_ID::BGM, true);

    // �V�[���}�l�[�W���[������
    CSceneManager::GetInstance().Initialize();
}

/*
 *  �X�V
 */
void
CGameManager::Update(void)
{

    // �V�[���}�l�[�W���[�X�V
    CSceneManager::GetInstance().Update();
}

/*
 *  �`��
 */
void
CGameManager::Draw(void)
{
    // �V�[���}�l�[�W���[�`��
    CSceneManager::GetInstance().Draw();
    CSceneManager::GetInstance().DrawSceneEffect();
}

/*
 *  ���
 */
void
CGameManager::Finalize(void)
{
    // �V�[���}�l�[�W���[���
    CSceneManager::GetInstance().Finalize();
}

/*
 *  �R���X�g���N�^
 */
CGameManager::CGameManager(void)
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
CGameManager::CGameManager(const CGameManager& rhs)
{
    (void)rhs;
}

/*
 *  �f�X�g���N�^
 */
CGameManager::~CGameManager(void)
{
}

/*
 *  ������Z�q
 */
CGameManager&
CGameManager::operator=(const CGameManager& rhs)
{
    (void)rhs;

    return *this;
}
