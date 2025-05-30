
/*!
 *  @file       scene_manager.cpp
 *  @brief      �V�[���Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "scene_manager.h"
#include "scene\title\title.h"
#include "scene\game_roll_and_reveal\game_roll_and_reveal.h"
#include "scene\select_skill\select_skill.h"
#include "scene\game\game.h"
#include "scene\game\fallout_game\fallout_game.h"
#include "scene\game\daruma_falldown_game\daruma_falldown_game.h"
#include "scene\game\dodgeball_game\dodgeball_game.h"
#include "scene\game\belt_conveyor_game\belt_conveyor_game.h"
#include "scene\minigame_result\minigame_result.h"
#include "scene\game_result\game_result.h"
#include "scene\entry\entry.h"
#include "../ui_manager/ui_manager.h"
#include "../controller_manager/controller_manager.h"
#include "../effect_manager/effect_manager.h"
#include "../ui_manager/ui/pause/pause.h"

const int               CSceneManager::m_fade_speed = 10;
const float             CSceneManager::m_wait_time = 0.0f;

/*
 *  �C���X�^���X�̎擾
 */
CSceneManager&
CSceneManager::GetInstance(void)
{
    static CSceneManager instance;

    return instance;
}

/*
 *  ������
 */
void
CSceneManager::Initialize(void)
{
    // ���[�g�V�[������
    m_NextSceneID = SCENE_ID::TITLE;

    // �V�[���ύX
    m_State = STATE::SCENE_CHANGE;

    m_Timer.SetUp(m_wait_time);
    m_FadeSpeed = m_fade_speed;
    m_FadeColor = 0x00ffffff;
    m_PauseController = nullptr;
}

/*
 *  �X�V
 */
void
CSceneManager::Update(void)
{
    switch (m_State)
    {
    case STATE::FADEIN:          FadeIn();      break;
    case STATE::SCENE_UPDATE:    SceneUpdate();  break;
    case STATE::FADEOUT:         FadeOut();     break;
    case STATE::SCENE_CHANGE:    SceneChange(); break;
    }
    CUIManager& um = CUIManager::GetInstance();
    um.Update();

    CEffectManager& em = CEffectManager::GetInstance();
    CControllerManager& cm = CControllerManager::GetInstance();

    if(m_PauseController == nullptr)
        m_PauseController = cm.GetSpecifiedButtonDownController(BUTTON_ID::START);
    if (m_PauseController == nullptr) return;
        m_PauseController->Update();
    if (m_PauseController->GetButtonDown(BUTTON_ID::START) && GetLastSceneID() != SCENE_ID::TITLE && m_State == STATE::SCENE_UPDATE)
    {
        Pause();
    }
}

/*
 *  �`��
 */
void
CSceneManager::Draw(void)
{
    // �V�[���`��
    if (m_SceneList.empty()) return;

    SCENE_LIST::iterator it = m_SceneList.begin();

    while (it != m_SceneList.end())
    {
        (*it)->Draw();

        ++it;
    }
    CUIManager::GetInstance().Draw();

}

/*
 *  �V�[���G�t�F�N�g�`��
 */
void
CSceneManager::DrawSceneEffect(void)
{
    vivid::DrawTexture("data\\Textures\\white.png", vivid::Vector2(), m_FadeColor);

}

/*
 *  ���
 */
void
CSceneManager::Finalize(void)
{
    // �V�[�����
    if (m_SceneList.empty()) return;

    SCENE_LIST::iterator it = m_SceneList.begin();

    while (it != m_SceneList.end())
    {
        (*it)->Finalize();

        delete (*it);

        it = m_SceneList.erase(it);

        continue;
    }

    m_SceneList.clear();
}

/*
 *  �V�[���؊���
 */
void
CSceneManager::ChangeScene(SCENE_ID id)
{
    // ���̃V�[��ID��o�^
    m_NextSceneID = id;

    m_ChangeScene = true;
}

void CSceneManager::PushScene(SCENE_ID id)
{
    CreateScene(id);
}

void CSceneManager::RemoveScene(SCENE_ID id)
{
    if (m_SceneList.size() <= 1) return;

    SCENE_LIST::iterator it = m_SceneList.begin();
    while (it != m_SceneList.end())
    {
        IScene* scene = (IScene*)(*it);

        if (scene->GetSceneID() == id)
        {
            scene->SetActive(false);
            return;
        }
        ++it;
    }
}

CSceneManager::SCENE_LIST CSceneManager::GetList()
{
    return m_SceneList;
}

bool CSceneManager::Pausing(void)
{
    return m_PauseFlag;
}

void CSceneManager::SetPauseFlag(bool flag)
{
    m_PauseFlag = flag;
}

SCENE_ID CSceneManager::GetLastSceneID(void)
{
    if (!m_SceneList.empty())
    {
        SCENE_LIST::iterator it = m_SceneList.end();
        --it;

        return (*it)->GetSceneID();
    }
    else
        return SCENE_ID::DUMMY;
}

void CSceneManager::Pause()
{
    CUIManager& um = CUIManager::GetInstance();

    CEffectManager& em = CEffectManager::GetInstance();

    if (m_PauseFlag == false)
        em.PauseAllEffect();
    else
        em.ResumeAllEffect();


    if (m_PauseFlag)
    {
        um.Delete(UI_ID::PAUSE);
        m_PauseController = nullptr;
    }
    else
    {
        CPause* pause = (CPause*)um.Create(UI_ID::PAUSE);
        pause->SetPauseController(m_PauseController);
    }
    m_PauseFlag ^= true;

}

/*
 *  �R���X�g���N�^
 */
CSceneManager::CSceneManager(void)
    : m_SceneList()
    , m_CurrentSceneID(SCENE_ID::DUMMY)
    , m_NextSceneID(SCENE_ID::DUMMY)
    , m_ChangeScene(false)
    , m_PauseController(nullptr)
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
CSceneManager::CSceneManager(const CSceneManager& rhs)
{
    (void)rhs;

}

/*
 *  �f�X�g���N�^
 */
CSceneManager::~CSceneManager(void)
{
}

/*
 *  ������Z�q
 */
CSceneManager&
CSceneManager::operator=(const CSceneManager& rhs)
{
    (void)rhs;

    return *this;
}

/*
 *  �V�[������
 */
IScene*
CSceneManager::CreateScene(SCENE_ID id)
{
    //ID����ɃV�[��������
    IScene* scene = nullptr;

    switch (id)
    {
    case SCENE_ID::TITLE:                   scene = new CTitle();               break;
    case SCENE_ID::SELECT_SKILL:            scene = new CSelectSkill();         break;
    case SCENE_ID::GAME_ROLL_AND_REVEAL:   scene = new CGameRollAndReveal();  break;
    case SCENE_ID::FALL_GAME:               scene = new CFallOutGame();         break;
    case SCENE_ID::DARUMA_FALLDOWN_GAME:    scene = new CDaruma_FallDownGame(); break;
    case SCENE_ID::DODGEBALL_GAME:          scene = new CDodgeBallGame();       break;
    case SCENE_ID::BELTCONVEYOR_GAME:       scene = new CBeltConveyorGame();    break;
    case SCENE_ID::MINIGAME_RESULT:         scene = new CMiniGameResult();      break;
    case SCENE_ID::GAME_RESULT:             scene = new CGameResult();          break;
    case SCENE_ID::ENTRY:                   scene = new CEntry();               break;
    }
    m_SceneList.push_back(scene);
    
    //������
    scene->Initialize(id);

    //���������̒����𔽉f���邽�߁A1�t���[���������X�V����
    scene->Update();

    return scene;
}

/*
 *  �t�F�[�h�C��
 */
void
CSceneManager::FadeIn(void)
{
    unsigned int alpha = vivid::alpha::GetAlpha(m_FadeColor);
    if (alpha == 0u)
    {
        m_FadeSpeed = m_fade_speed;

        // �V�[���X�V
        m_State = STATE::SCENE_UPDATE;
    }
    m_FadeColor = vivid::alpha::AdjustAlpha(m_FadeColor, m_FadeSpeed);

}

/*
 *  �V�[���X�V
 */
void
CSceneManager::SceneUpdate(void)
{
    // �V�[���X�V
    if (m_SceneList.empty()) return;

    SCENE_LIST::iterator it = m_SceneList.begin();

    while (it != m_SceneList.end())
    {
        IScene* scene = (IScene*)(*it);

        //�A�N�e�B�u���|�[�Y���łȂ�
        if(scene->GetSceneState() == SCENE_STATE::ACTIVE && !m_PauseFlag)
            scene->Update();

        if (!scene->IsActive())
        {
            scene->Finalize();

            delete scene;

            it = m_SceneList.erase(it);

            continue;
        }

        ++it;
    }

    // �V�[���ύX������
    if (m_CurrentSceneID != m_NextSceneID || m_ChangeScene)
    {
        // �t�F�[�h�A�E�g
        m_State = STATE::FADEOUT;

        m_ChangeScene = false;
    }
}

/*
 *  �t�F�[�h�A�E�g
 */
void
CSceneManager::FadeOut(void)
{
    unsigned int alpha = vivid::alpha::GetAlpha(m_FadeColor);
    if (alpha == 255u)
    {
        m_Timer.Update();
        if (m_Timer.Finished())
        {
            m_Timer.Reset();
            // �V�[���ύX
            m_State = STATE::SCENE_CHANGE;
            m_FadeSpeed = -m_fade_speed;
        }
    }

    m_FadeColor = vivid::alpha::AdjustAlpha(m_FadeColor, m_FadeSpeed);
}

/*
 *  �V�[���ύX
 */
void
CSceneManager::SceneChange()
{
    if (!m_SceneList.empty())
    {
        SCENE_LIST::iterator it = m_SceneList.begin();
        while (it != m_SceneList.end())
        {
            IScene* scene = (IScene*)(*it);
            if (scene->IsActive() == true)
            {
                scene->Finalize();

                delete scene;

                it = m_SceneList.erase(it);

                scene = nullptr;
            }

        }
    }

    // �V�����V�[������
    CreateScene(m_NextSceneID);

    m_CurrentSceneID = m_NextSceneID;

    // �t�F�[�h�C��
    m_State = STATE::FADEIN;
}

IScene* CSceneManager::GetScene(SCENE_ID scene_id)
{
    if (m_SceneList.empty()) return nullptr;

    SCENE_LIST::iterator it = m_SceneList.begin();

    while (it != m_SceneList.end())
    {
        IScene* scene = (IScene*)(*it);

        if (scene->IsActive() && scene->GetSceneID() == scene_id)
            return scene;

        ++it;
    }
    return nullptr;
}