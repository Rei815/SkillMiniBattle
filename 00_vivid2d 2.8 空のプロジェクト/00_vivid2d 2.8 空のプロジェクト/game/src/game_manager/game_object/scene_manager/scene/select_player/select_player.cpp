#include "select_player.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../data_manager/data_manager.h"

const vivid::Vector2    CSelectPlayer::m_player_num_ui_pos[(int)UNIT_ID::NONE] =
{
    vivid::Vector2(0,0),
    vivid::Vector2(vivid::WINDOW_WIDTH / 4.0f * 1.0f, vivid::WINDOW_HEIGHT / 3.0f * 2.0f),
    vivid::Vector2(vivid::WINDOW_WIDTH / 4.0f * 2.0f, vivid::WINDOW_HEIGHT / 3.0f * 2.0f),
    vivid::Vector2(vivid::WINDOW_WIDTH / 4.0f * 3.0f, vivid::WINDOW_HEIGHT / 3.0f * 2.0f)
};
const float             CSelectPlayer::m_player_num_ui_scale = 1.0f;


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

    CStage::GetInstance().Initialize();

    CDataManager::GetInstance().Initialize();

    CUIManager::GetInstance().Initialize();

    CUIManager::GetInstance().Create(UI_ID::MENU_BG);

    CUIManager::GetInstance().Create(UI_ID::SCENE_TITLE);

    for (int i = 1; i < (int)UNIT_ID::NONE; i++)
    {
        CUI* ui = CUIManager::GetInstance().Create(UI_ID::PLAYER_NUM_SELECT);

        m_PlayerNumUI[i] = dynamic_cast<CPlayerNumSelect*>(ui);

        if (m_PlayerNumUI[i] == nullptr)
        {
            ui->SetActive(false);
            continue;
        }

        m_PlayerNumUI[i]->SetData(m_player_num_ui_pos[i], i + 1, m_player_num_ui_scale);
    }
}

void CSelectPlayer::Update(void)
{
    CDataManager& dm = CDataManager::GetInstance();
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::A))
        dm.SetCurrentPlayer(dm.GetCurrentPlayer() - 1);
    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::D))
        dm.SetCurrentPlayer(dm.GetCurrentPlayer() + 1);

    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
    {
        CSceneManager::GetInstance().ChangeScene(SCENE_ID::SELECTMODE);
    }
    CStage::GetInstance().Update();

    for (int i = 1; i < (int)UNIT_ID::NONE; i++)
    {

        if (i + 1 == dm.GetCurrentPlayer())
            m_PlayerNumUI[i]->SetSelected(true);
        else
            m_PlayerNumUI[i]->SetSelected(false);
    }

    CUIManager::GetInstance().Update();
}

void CSelectPlayer::Draw(void)
{
    CUIManager::GetInstance().Draw();

    vivid::DrawText(50, "スキルミニバトル", vivid::Vector2(vivid::WINDOW_WIDTH / 2 - vivid::GetTextWidth(50, "スキルミニバトル") / 2, vivid::WINDOW_HEIGHT / 4));

    vivid::DrawText(20, "ADキーで人数の増減, ENTERキーで決定", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));
    vivid::DrawText(20, "現在" + std::to_string(CDataManager::GetInstance().GetCurrentPlayer()) + "人", vivid::Vector2(500, vivid::WINDOW_HEIGHT - 20));

}

void CSelectPlayer::Finalize(void)
{
    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        m_PlayerNumUI[i] = nullptr;
    }

    IScene::Finalize();

    CStage::GetInstance().Finalize();

    CUIManager::GetInstance().Finalize();
}
