#include "select_game.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../data_manager/data_manager.h"
#include "../../../animation_manager/animation/animation.h"
#include "../../../animation_manager/animation_manager.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../ui_manager/ui/game_video/game_video.h"
#include "../../../ui_manager/ui/player_ready/player_ready.h"
#include "../../../controller_manager/controller_manager.h"

const int CSelectGame::m_games_num = 4;
const float CSelectGame::m_circle_radius = 500.0f;
CSelectGame::CSelectGame(void)
    : m_SelectedGameFlag(false)
    , m_GameInfomationFlag(false)
    , m_FirstSceneUIParent(nullptr)
    , m_SecondSceneUIParent(nullptr)
    , m_SelectedGameID(GAME_ID::MAX)
    , m_PlaneGameImage(nullptr)
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
    CUIManager::UI_LIST uiList = CUIManager::GetInstance().GetList();

    //ミニゲームから戻ってきた場合の処理
    if (uiList.size() == 0)
    {
        CUIManager::GetInstance().Initialize();
        CUIManager::GetInstance().Create(UI_ID::TITLE_LOGO);
        CSoundManager::GetInstance().Play_BGM(BGM_ID::READY_BGM, true);
    }

    //ゲームの画像を円状かつ均等に配置
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

    //ミニゲームの決定
    int game_id = rand() % (int)GAME_ID::MAX;
    m_SelectedGameID = (GAME_ID)game_id;
    CDataManager::GetInstance().SetGameID(m_SelectedGameID);

    uiList = CUIManager::GetInstance().GetList();
    CUIManager::UI_LIST::iterator it = uiList.begin();

    //上昇させるゲーム画像をキープ
    while (it != uiList.end())
    {
        CUI* ui = (CUI*)(*it);

        ++it;

        if (ui->GetUI_ID() != UI_ID::PLANE_GAME_IMAGE) continue;
        CPlaneGameImage* plameGameImage = (CPlaneGameImage*)ui;
        if (plameGameImage->GetGameID() == m_SelectedGameID)
        {
            m_PlaneGameImage = plameGameImage;
        }
    }
    CControllerManager& cm = CControllerManager::GetInstance();
    cm.Initialize();

}

void CSelectGame::Update(void)
{
    CControllerManager& cm = CControllerManager::GetInstance();
    CController* controller_1 = cm.GetController(CONTROLLER_ID::ONE);

    cm.Update();

    CCamera::GetInstance().Update();
    CUIManager& um = CUIManager::GetInstance();
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
    if ((vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN) || controller_1->GetButtonDown(INPUT_ID::B)) && m_FirstSceneUIParent == nullptr && m_SelectedGameFlag == false)
    {
        uiList = CUIManager::GetInstance().GetList();
        it = uiList.begin();
        while (it != uiList.end())
        {
            CPlaneGameImage* planeGameImage = (CPlaneGameImage*)(*it);

            ++it;
            if (planeGameImage->GetUI_ID() == UI_ID::TITLE_LOGO) continue;

            if (planeGameImage->GetGameID() == m_SelectedGameID)
            {
                m_PlaneGameImage = planeGameImage;
                IAnimation* animation = nullptr;
                animation = am.Create(ANIMATION_ID::PLANE_UP, m_PlaneGameImage);
                m_PlaneGameImage->SetAnimation(animation);
                m_SelectedGameFlag = true;
            }
            else
            {
                planeGameImage->SetAnimation(am.Create(ANIMATION_ID::PLANE_SCALE, planeGameImage));   // 選ばれていないものは小さくなる
            }

        }
    }
    if (m_SelectedGameFlag == true)
    {
        //上昇アニメーションが終了している
        if (m_PlaneGameImage->GetAnimation() == nullptr && m_GameInfomationFlag == false)
        {
            m_PlaneGameImage->SetActive(false);
            m_GameInfomationFlag = true;
            um.Create(UI_ID::MENU_BG);
            um.Create(UI_ID::MINIGAME_OVERVIEW);
            um.Create(UI_ID::MINIGAME_MANUAL);
            um.Create(UI_ID::PLAYER_READY);

            CGameVideo* gameVideo = (CGameVideo*)um.Create(UI_ID::GAME_VIDEO);
            gameVideo->SetGameVideo(m_SelectedGameID);
            um.Create(UI_ID::MINIGAME_TITLE);

            um.Delete(m_FirstSceneUIParent);
            m_SecondSceneUIParent = (CSceneUIParent*)um.Create(UI_ID::SCENE_UI_PARENT, vivid::Vector2(vivid::GetWindowWidth() / 2, -vivid::GetWindowHeight() / 2));
            m_SecondSceneUIParent->SetState(CSceneUIParent::STATE::MOVE_ONE);
        }
    }
//#ifdef _DEBUG
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::ONE))
    {
        m_SelectedGameID = GAME_ID::DARUMA_FALL_DOWN_GAME;
        dm.SetGameID(m_SelectedGameID);

        CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);
    }

    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::TWO))
    {
        m_SelectedGameID = GAME_ID::FALLOUT_GAME;
        dm.SetGameID(m_SelectedGameID);

        CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);
    }
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::THREE))
    {
        m_SelectedGameID = GAME_ID::DODGE_BALL_GAME;
        dm.SetGameID(m_SelectedGameID);

        CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);
    }
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::FOUR))
    {
        m_SelectedGameID = GAME_ID::BELT_CONVEYOR_GAME;
        dm.SetGameID(m_SelectedGameID);

        CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);
    }
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::FIVE))
    {
        m_SelectedGameID = GAME_ID::MAZE_GAME;
        dm.SetGameID(m_SelectedGameID);

        CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);
    }
    it = uiList.begin();
    while (it != uiList.end())
    {
        CUI* ui = (CUI*)(*it);

        ++it;
        if (ui->GetUI_ID() != UI_ID::PLANE_GAME_IMAGE) continue;
        CPlaneGameImage* plameGameImage = (CPlaneGameImage*)ui;
        if (plameGameImage->GetGameID() == m_SelectedGameID)
        {
            m_PlaneGameImage = plameGameImage;
        }
    }

//#endif

    if (m_SecondSceneUIParent)
    {
        CPlayerReady* playerReady = (CPlayerReady*)CUIManager::GetInstance().GetUI(UI_ID::PLAYER_READY);
        if (playerReady == nullptr) return;
        //ミニゲーム情報が中心にある状態
        if (playerReady->GetReadyFlag() == true && m_SecondSceneUIParent->GetState() == CSceneUIParent::STATE::WAIT && m_GameInfomationFlag == true)
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
#if _DEBUG
    vivid::DrawText(20, "1キーでだるまさんがころんだゲーム", vivid::Vector2(0, 0));
    vivid::DrawText(20, "2キーでフォールアウトゲーム", vivid::Vector2(0, 30));
    vivid::DrawText(20, "3キーでドッジボールゲーム", vivid::Vector2(0, 60));
    vivid::DrawText(20, "4キーでベルトコンベアゲーム", vivid::Vector2(0, 90));
    vivid::DrawText(20, std::to_string((int)m_SelectedGameID + 1), vivid::Vector2(0, 110));

#endif // _DEBUG


}

void CSelectGame::Finalize(void)
{
    IScene::Finalize();

    CCamera::GetInstance().Finalize();

    CUIManager::GetInstance().Delete(m_FirstSceneUIParent);
    CUIManager::GetInstance().Delete(m_SecondSceneUIParent);
}