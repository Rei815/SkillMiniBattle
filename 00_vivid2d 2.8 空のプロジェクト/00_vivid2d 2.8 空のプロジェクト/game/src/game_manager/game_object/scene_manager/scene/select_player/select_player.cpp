#include "select_player.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../data_manager/data_manager.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../controller_manager/controller_manager.h"

const vivid::Vector2    CSelectPlayer::m_player_num_ui_pos[(int)UNIT_ID::NONE] =
{
    vivid::Vector2(0,0),
    vivid::Vector2(vivid::WINDOW_WIDTH / 4.0f * 1.0f, vivid::WINDOW_HEIGHT / 3.0f * 2.0f),
    vivid::Vector2(vivid::WINDOW_WIDTH / 4.0f * 2.0f, vivid::WINDOW_HEIGHT / 3.0f * 2.0f),
    vivid::Vector2(vivid::WINDOW_WIDTH / 4.0f * 3.0f, vivid::WINDOW_HEIGHT / 3.0f * 2.0f)
};
const float             CSelectPlayer::m_player_num_ui_scale = 0.4f;


CSelectPlayer::CSelectPlayer(void)
    :m_PlayerNumUI{nullptr}
{

}

CSelectPlayer::~CSelectPlayer(void)
{
}

void CSelectPlayer::Initialize(SCENE_ID scene_id)
{
    IScene::Initialize(scene_id);

    CCamera::GetInstance().Initialize();

    CDataManager::GetInstance().Initialize();

    CUIManager& um = CUIManager::GetInstance();
    um.Create(UI_ID::TITLE_LOGO);

    um.Create(UI_ID::MENU_BG);

    um.Create(UI_ID::SCENE_TITLE);

    for (int i = 1; i < (int)UNIT_ID::NONE; i++)
    {
        CUI* ui = um.Create(UI_ID::PLAYER_NUM_SELECT);

        m_PlayerNumUI[i] = dynamic_cast<CPlayerNumSelect*>(ui);

        if (m_PlayerNumUI[i] == nullptr)
        {
            ui->SetActive(false);
            continue;
        }

        m_PlayerNumUI[i]->SetData(m_player_num_ui_pos[i], i + 1, m_player_num_ui_scale);
    }

    IScene* previousScene = (*CSceneManager::GetInstance().GetList().begin());

    //このシーンが作られた際にタイトルからなのかセレクトモードシーンから作られたかで動きを変える
    if (previousScene->GetSceneID() == SCENE_ID::TITLE)
    {
        m_SceneUIParent = (CSceneUIParent*)um.Create(UI_ID::SCENE_UI_PARENT, vivid::Vector2(vivid::GetWindowWidth() / 2, -vivid::GetWindowHeight() / 2));
        m_SceneUIParent->SetState(CSceneUIParent::STATE::MOVE_ONE);
    }
    //else if(previousScene->GetSceneID() == SCENE_ID::SELECTMODE)
    //{
    //    m_SceneUIParent = (CSceneUIParent*)CUIManager::GetInstance().Create(UI_ID::SCENE_UI_PARENT, vivid::Vector2(vivid::GetWindowWidth() / 2, vivid::GetWindowHeight() * 1.5));
    //    m_SceneUIParent->SetState(CSceneUIParent::STATE::BACK_ONE);
    //}
}

void CSelectPlayer::Update(void)
{
    CControllerManager& cm = CControllerManager::GetInstance();
    CController* controller_1 = cm.GetController(CONTROLLER_ID::ONE);
    cm.Update();

    CDataManager& dm = CDataManager::GetInstance();
    int currentPlayer = dm.GetCurrentPlayer();
    for (int i = 1; i < (int)UNIT_ID::NONE; i++)
    {
        if (i + 1 == dm.GetCurrentPlayer())
            m_PlayerNumUI[i]->SetSelected(true);
        else
            m_PlayerNumUI[i]->SetSelected(false);
    }
    if (m_SceneUIParent)
    {
        if (m_SceneUIParent->GetState() == CSceneUIParent::STATE::WAIT)
        {
            if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::A) || (!controller_1->GetLeftHorizontal() && controller_1->GetLeftStick().x == -1.0f))
            {
                controller_1->SetLeftHorizontal(true);
                currentPlayer--;
                dm.SetCurrentPlayer(currentPlayer);
            }
            if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::D) || (!controller_1->GetLeftHorizontal() && controller_1->GetLeftStick().x == 1.0f))
            {
                controller_1->SetLeftHorizontal(true);

                currentPlayer++;
                dm.SetCurrentPlayer(currentPlayer);
            }

            if ((vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::BACK) || controller_1->GetButtonDown(BUTTON_ID::A)))
            {
                m_SceneUIParent->SetState(CSceneUIParent::STATE::BACK_ONE);
                CSceneManager::GetInstance().PushScene(SCENE_ID::TITLE);
                CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);
            }

            if ((vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN) || controller_1->GetButtonDown(BUTTON_ID::B)))
            {
                CSceneManager::GetInstance().PushScene(SCENE_ID::SELECTGAME);
                m_SceneUIParent->SetState(CSceneUIParent::STATE::MOVE_ONE);
                CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);
            }
        }

        if (m_SceneUIParent->GetState() != CSceneUIParent::STATE::FINISH) return;

        const float min_height = -vivid::GetWindowHeight() / 2;
        const float max_height = vivid::GetWindowHeight() * 1.5;
        if (m_SceneUIParent->GetPosition().y <= min_height || max_height <= m_SceneUIParent->GetPosition().y)
            CSceneManager::GetInstance().PopScene(SCENE_ID::SELECTPLAYER);
    }

}

void CSelectPlayer::Draw(void)
{
}

void CSelectPlayer::Finalize(void)
{
    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        m_PlayerNumUI[i] = nullptr;
    }

    IScene::Finalize();
    CUIManager::GetInstance().Delete(m_SceneUIParent);
}
