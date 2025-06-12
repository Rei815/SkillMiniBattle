#include "minigame_result.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../ui_manager/ui_manager.h"
#include "../../../data_manager/data_manager.h"
#include "../../../animation_manager/animation_manager.h"
#include "../../../ui_manager/ui/player_icon/player_icon.h"
#include "../../../ui_manager/ui/notice/notice.h"
#include "../../../controller_manager/controller_manager.h"

const vivid::Vector2  CMiniGameResult::m_origin_key_pos = vivid::Vector2(40, 250);
const vivid::Vector2  CMiniGameResult::m_origin_icon_pos = vivid::Vector2(85, 100);
const vivid::Vector2  CMiniGameResult::m_origin_notice_pos = vivid::Vector2(-70, -70);
const float  CMiniGameResult::m_key_offset = 90.0f;
const float  CMiniGameResult::m_icon_offset = 300.0f;
const float  CMiniGameResult::m_notice_offset = 300.0f;
const float  CMiniGameResult::m_players_key_offset = 300.0f;
const vivid::Vector2  CMiniGameResult::m_notice_scale = vivid::Vector2(0.65f, 0.70f);
CMiniGameResult::CMiniGameResult(void)
{

}

CMiniGameResult::~CMiniGameResult(void)
{
}

void CMiniGameResult::Initialize(SCENE_ID scene_id)
{
    IScene::Initialize(scene_id);
    CAnimationManager::GetInstance().Initialize();
    CDataManager& dm = CDataManager::GetInstance();
    CUIManager& um = CUIManager::GetInstance();
    vivid::Vector2 offsetPos;
    int firstPlayerID = (int)dm.GetLastGameRanking(0);
    for (int i = 0; i < dm.GetCurrentJoinPlayer(); i++)
    {
        vivid::Vector2 noticePos = m_origin_notice_pos;
        noticePos.x += m_notice_offset * i;
        std::shared_ptr<CNotice> notice = dynamic_pointer_cast<CNotice>(um.Create(UI_ID::NOTICE, noticePos));
        notice->SetScale(m_notice_scale);
        //背景表示
        for (int j = 0; j < dm.GetRequiredWins(); j++)
        {
            offsetPos = vivid::Vector2((m_key_offset * j) + (m_players_key_offset * i), 0);
            um.Create(UI_ID::KEY_BG, m_origin_key_pos + offsetPos);
        }

        vivid::Vector2 iconPos = m_origin_icon_pos;
        iconPos.x += m_icon_offset * i;

        std::shared_ptr<CPlayerIcon> playerIcon = dynamic_pointer_cast<CPlayerIcon>(um.Create(UI_ID::PLAYER_ICON, iconPos));
        playerIcon->SetPlayerID((UNIT_ID)i);

        //これまでの勝利数表示
        //一位のプレイヤー以外は勝利数そのままで表示
        int playerWin = dm.GetPlayerWin(i);
        if (i == firstPlayerID)
            playerWin--;
        for (int j = 0; j < playerWin; j++)
        {
            offsetPos = vivid::Vector2((m_key_offset * j) + (m_players_key_offset * i), 0);
            um.Create(UI_ID::KEY, m_origin_key_pos + offsetPos);
        }

    }

    m_SceneUIParent = dynamic_pointer_cast<CSceneUIParent>(um.Create(UI_ID::SCENE_UI_PARENT, vivid::Vector2(vivid::GetWindowWidth() / 2, -vivid::GetWindowHeight() / 2)));
    m_SceneUIParent->SetState(CSceneUIParent::STATE::MOVE_ONE);

}

void CMiniGameResult::Update(void)
{
    CDataManager& dm = CDataManager::GetInstance();
    CControllerManager& cm = CControllerManager::GetInstance();
    std::shared_ptr<CController> controller_1 = cm.GetController(CONTROLLER_ID::ONE);
    cm.Update();

    CAnimationManager::GetInstance().Update();
    if (m_SceneUIParent)
    {
        if (m_SceneUIParent->GetState() == CSceneUIParent::STATE::WAIT)
        {
            int firstPlayerID = (int)dm.GetLastGameRanking(0);

            //アニメーション付きのカギの表示(一位のみ)

            vivid::Vector2 offsetPos = vivid::Vector2((m_key_offset * (dm.GetPlayerWin(firstPlayerID) - 1)) + (m_players_key_offset * firstPlayerID), 0);

            std::shared_ptr<CUI> animationKey = CUIManager::GetInstance().Create(UI_ID::KEY, m_origin_key_pos + offsetPos);
            CAnimationManager::GetInstance().Create(ANIMATION_ID::KEY_SCALE, animationKey);

            m_SceneUIParent = nullptr;

        }
    }
    if (cm.GetAnyControllerButtonDown(BUTTON_ID::ANY))
    {

        SCENE_ID sceneID = SCENE_ID::GAME_ROLL_AND_REVEAL;
        for (int i = 0; i < dm.GetCurrentJoinPlayer(); i++)
        {
            if (dm.GetPlayerWin(i) == dm.GetRequiredWins())
            {
                sceneID = SCENE_ID::GAME_RESULT;
                break;
            }
        }
        CSceneManager::GetInstance().ChangeScene(sceneID);
    }
}

void CMiniGameResult::Draw(void)
{
}

void CMiniGameResult::Finalize(void)
{
    CUIManager::GetInstance().Finalize();
    CEffectManager::GetInstance().Finalize();
    CAnimationManager::GetInstance().Finalize();
    IScene::Finalize();


}
