#include "game_manager.h"
#include "game_object\game_object.h"
#include "game_object/sound_manager/sound_manager.h"
#include "game_object/scene_manager/scene_manager.h"

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
    // �T�E���h�}�l�[�W���[�擾
    CSoundManager& sound = CSoundManager::GetInstance();

    // �T�E���h�ǂݍ���
    sound.Load_SE();
    sound.Load_BGM();

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
