#include "select_game.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../data_manager/data_manager.h"
#include "../../../animation_manager/animation/animation.h"
#include "../../../animation_manager/animation_manager.h"
#include "../../../sound_manager/sound_manager.h"

const int CSelectGame::m_games_num = 3;
const float CSelectGame::m_circle_radius = 500.0f;
CSelectGame::CSelectGame(void)
    : m_SelectedGameFlag(false)
    , m_GameInfomationFlag(false)
    , m_FirstSceneUIParent(nullptr)
    , m_SecondSceneUIParent(nullptr)
    , m_SelectedGameID(GAME_ID::MAX)
{

}

CSelectGame::~CSelectGame(void)
{
}

void CSelectGame::Initialize(SCENE_ID scene_id)
{
    IScene::Initialize(scene_id);

    CCamera::GetInstance().Initialize();
    CCamera::GetInstance().SetPosition(CVector3(0.0f, 600.0f, -1000.0f));
    CCamera::GetInstance().SetDirection(CVector3(0.0f, 0.0f, 1.0f));
    CAnimationManager::GetInstance().Initialize();
    for (int i = 0; i < m_games_num; i++)
    {
        CTransform transform;
        const float rad = i / (float)m_games_num * DX_TWO_PI;
        const float _x = m_circle_radius * sin(rad);
        const float _z = m_circle_radius * cos(rad);
        transform.rotation.y = i * (360.0f / (float)m_games_num);
        transform.position.y = 500.0f;
        transform.position.x = 0.0f;//_x;
        transform.position.z = -m_circle_radius;//_z;
        
        CPlaneGameImage* planeGameImage = dynamic_cast<CPlaneGameImage*>(CUIManager::GetInstance().Create(UI_ID::PLANE_GAME_IMAGE, transform));
        planeGameImage->SetGameID((GAME_ID)i);
    }
    // Ｘ軸のマイナス方向のディレクショナルライトに変更
    ChangeLightTypeDir(VGet(1.0f, -1.0f, 1.0f));

    IScene* scene = (*CSceneManager::GetInstance().GetList().begin());

    m_FirstSceneUIParent = (CSceneUIParent*)CUIManager::GetInstance().Create(UI_ID::SCENE_UI_PARENT, vivid::Vector2(vivid::GetWindowWidth() / 2, -vivid::GetWindowHeight() / 2));
    m_FirstSceneUIParent->SetState(CSceneUIParent::STATE::MOVE_ONE);

    int game_id = rand() % (int)GAME_ID::MAX;
    m_SelectedGameID = (GAME_ID)game_id;
    CDataManager::GetInstance().SetGameID(m_SelectedGameID);

    CUIManager::UI_LIST uiList = CUIManager::GetInstance().GetList();
    CUIManager::UI_LIST::iterator it = uiList.begin();
    while (it != uiList.end())
    {
        CUI* ui = (CUI*)(*it);

        ++it;
        if (ui->GetUI_ID() == UI_ID::TITLE_LOGO) continue;
        CPlaneGameImage* plameGameImage = (CPlaneGameImage*)ui;
        if (plameGameImage->GetGameID() == m_SelectedGameID)
        {
            m_planeGameImage = (CPlaneGameImage*)ui;
        }
    }

}

void CSelectGame::Update(void)
{
    CCamera::GetInstance().Update();
    CUIManager& um = CUIManager::GetInstance();
    CUIManager::GetInstance().Update();
    CAnimationManager::GetInstance().Update();

    CDataManager& dm = CDataManager::GetInstance();
    CAnimationManager& am = CAnimationManager::GetInstance();

    CUIManager::UI_LIST uiList = CUIManager::GetInstance().GetList();
    CUIManager::UI_LIST::iterator it = uiList.begin();
    if (m_FirstSceneUIParent)
    {
        if (m_FirstSceneUIParent->GetState() == CSceneUIParent::STATE::WAIT)
        {
            while (it != uiList.end())
            {
                CUI* ui = (CUI*)(*it);

                ++it;
                if (ui->GetUI_ID() != UI_ID::PLANE_GAME_IMAGE) continue;
                CPlaneGameImage* plameGameImage = (CPlaneGameImage*)ui;
                plameGameImage->SetParent(nullptr);
            }

            m_FirstSceneUIParent->SetActive(false);
            m_FirstSceneUIParent = nullptr;
        }

    }
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN) && m_FirstSceneUIParent== nullptr && m_SelectedGameFlag == false)
    {

        while (it != uiList.end())
        {
            CPlaneGameImage* planeGameImage = (CPlaneGameImage*)(*it);

            ++it;
            if (planeGameImage->GetUI_ID() == UI_ID::TITLE_LOGO) continue;

            if (planeGameImage->GetGameID() == m_SelectedGameID)
            {
                m_planeGameImage = planeGameImage;
                IAnimation* animation = am.Create(ANIMATION_ID::PLANE_UP, m_planeGameImage);
                m_planeGameImage->SetAnimation(animation);
                m_SelectedGameFlag = true;
            }
            else
                am.Create(ANIMATION_ID::PLANE_SCALE, planeGameImage);   // 選ばれていないものは小さくなる

        }
    }
    if (m_SelectedGameFlag == true)
    {
        //上昇アニメーションが終了している
        if (m_planeGameImage->GetAnimation() == nullptr && m_GameInfomationFlag == false)
        {
            m_GameInfomationFlag = true;
            m_planeGameImage->SetParent(nullptr);
            vivid::Vector2 bgPos = vivid::Vector2(vivid::GetWindowWidth() / 2, vivid::GetWindowHeight() / 2);
            um.Create(UI_ID::MENU_BG, bgPos);
            um.Delete(m_FirstSceneUIParent);
            m_SecondSceneUIParent = (CSceneUIParent*)um.Create(UI_ID::SCENE_UI_PARENT, vivid::Vector2(vivid::GetWindowWidth() / 2, -vivid::GetWindowHeight() / 2));
            m_SecondSceneUIParent->SetState(CSceneUIParent::STATE::MOVE_ONE);

        }
#if _DEBUG
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::ONE))
    {
        _gameID = GAME_ID::DARUMA_FALL_DOWN_GAME;
        CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTSKILL);
        //CSceneManager::GetInstance().ChangeScene(SCENE_ID::DARUMAFALLDOWN);
    }

    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::TWO))
    {
        _gameID = GAME_ID::FALL_GAME;
        CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTSKILL);
        //CSceneManager::GetInstance().ChangeScene(SCENE_ID::FALLGAME);
    }
#if _DEBUG
    //if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::ONE))
    //{
    //    _gameID = GAME_ID::DARUMA_FALL_DOWN_GAME;
    //    CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTSKILL);
    //    //CSceneManager::GetInstance().ChangeScene(SCENE_ID::DARUMAFALLDOWN);
    //}

    //if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::TWO))
    //{
    //    _gameID = GAME_ID::FALL_GAME;
    //    CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTSKILL);
    //    //CSceneManager::GetInstance().ChangeScene(SCENE_ID::FALLGAME);
    //}

    //if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::THREE))
    //{
    //    _gameID = GAME_ID::DODGE_BALL_GAME;
    //    CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTSKILL);
    //    //CSceneManager::GetInstance().ChangeScene(SCENE_ID::DODGEBALLGAME);
    //}
    //if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::FOUR))
    //{
    //    _gameID = GAME_ID::DEBUG_GAME;
    //    CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTSKILL);
    //    //CSceneManager::GetInstance().ChangeScene(SCENE_ID::DODGEBALLGAME);
    //}
#endif

    if (m_SecondSceneUIParent)
    {
        if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN) && m_SecondSceneUIParent->GetState() == CSceneUIParent::STATE::WAIT && m_GameInfomationFlag == true)
        {
            CSceneManager::GetInstance().PushScene(SCENE_ID::SELECTSKILL);
            CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);

            m_SecondSceneUIParent->SetState(CSceneUIParent::STATE::MOVE_ONE);

        }

        if (m_SecondSceneUIParent->GetState() != CSceneUIParent::STATE::FINISH) return;

        const float min_height = -vivid::GetWindowHeight() / 2;
        const float max_height = vivid::GetWindowHeight() * 1.5;
        if (m_SecondSceneUIParent->GetPosition().y <= min_height || max_height <= m_SecondSceneUIParent->GetPosition().y)
            CSceneManager::GetInstance().PopScene(SCENE_ID::SELECTGAME);
    }

}

void CSelectGame::Draw(void)
{
    CUIManager::GetInstance().Draw();


    vivid::DrawText(20, "ゲーム選択中", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));
    vivid::DrawText(20, "1キーでだるまさんがころんだゲーム", vivid::Vector2(0, 0));
    vivid::DrawText(20, "2キーでフォールアウトゲーム", vivid::Vector2(0, 30));
    vivid::DrawText(20, "3キーでドッジボールゲーム", vivid::Vector2(0, 60));

}

void CSelectGame::Finalize(void)
{
    IScene::Finalize();

    CCamera::GetInstance().Finalize();

    CUIManager::GetInstance().Delete(m_FirstSceneUIParent);
    CUIManager::GetInstance().Delete(m_SecondSceneUIParent);


}
