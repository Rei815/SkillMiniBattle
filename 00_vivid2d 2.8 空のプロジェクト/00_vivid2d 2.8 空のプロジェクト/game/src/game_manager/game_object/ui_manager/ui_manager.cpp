#include "ui_manager.h"
#include "ui/pause/pause.h"
#include "ui/fallout_topic/fallout_topic.h"
#include "ui/fallout_topic_bg/fallout_topic_bg.h"
#include "ui/topic_shutter/topic_shutter.h"
#include "ui/plane_game_image/plane_game_image.h"
#include "ui/finish_backGround/finish_backGround.h"
#include "ui/skill_icon/skill_icon.h"
#include "ui/skill_gauge/skill_gauge.h"
#include "ui/skill_cursor/skill_cursor.h"
#include "ui/skill_name/skill_name.h"
#include "ui/skill_infomation/skill_infomation.h"
#include "ui/key/key.h"
#include "ui/key_bg/key_bg.h"
#include "ui/title_logo/title_logo.h"
#include "ui/start_game_count/start_game_count.h"
#include "ui/start_game_text/start_game_text.h"
#include "ui/fade/fade.h"
#include "ui/finish_game_text/finish_game_text.h"
#include "ui/game_bg/game_bg.h"
#include "ui/menu_bg/menu_bg.h"
#include "ui/menu_poster/menu_poster.h"
#include "ui/player_num_select/player_num_select.h"
#include "ui/scene_title/scene_title.h"
#include "ui/skill_video/skill_video.h"
#include "ui/scene_ui_parent/scene_ui_parent.h"
#include "ui/title_button/title_button.h"
#include "ui/game_video/game_video.h"
#include "ui/minigame_title/minigame_title.h"
#include "ui/minigame_manual/minigame_manual.h"
#include "ui/minigame_overview/minigame_overview.h"
#include "ui/player_ready/player_ready.h"
#include "ui/notice/notice.h"
#include "ui/notice_wide/notice_wide.h"
#include "ui/player_icon/player_icon.h"
#include "ui/text_overview/text_overview.h"
#include "ui/text_manual/text_manual.h"
#include "ui/concentration_line/concentration_line.h"
#include "ui/result_winner/result_winner.h"
#include "ui/entry_x_button/entry_x_button.h"
#include "ui/player_join/player_join.h"
#include "..\scene_manager\scene_manager.h"
 /*
  *  インスタンスの取得
  */
CUIManager&
CUIManager::
GetInstance(void)
{
    static CUIManager instance;

    return instance;
}

/*
 *  初期化
 */
void
CUIManager::
Initialize(void)
{
    m_UIList.clear();
}

/*
 *  更新
 */
void
CUIManager::Update(void)
{
    if (m_UIList.empty()) return;

    UI_LIST::iterator it = m_UIList.begin();

    while (it != m_UIList.end())
    {
        CUI* ui = dynamic_cast<CUI*>((*it).get());

        if(ui->GetUI_ID() == UI_ID::PAUSE || !CSceneManager::GetInstance().Pausing())
            ui->Update();
        SortList();
        if (!ui->IsActive())
        {
            ui->Finalize();

            it = m_UIList.erase(it);

            continue;
        }
        ++it;
    }
}

/*
 *  描画
 */
void CUIManager::Draw(void)
{
    if (m_UIList.empty()) return;

    UI_LIST::iterator it = m_UIList.begin();

    while (it != m_UIList.end())
    {

        (*it)->Draw();

        ++it;
    }
}

/*
 *  解放
 */
void CUIManager::Finalize(void)
{
    if (m_UIList.empty()) return;

    UI_LIST::iterator it = m_UIList.begin();

    while (it != m_UIList.end())
    {
        (*it)->Finalize();

        ++it;
    }

    m_UIList.clear();
}

CUI* CUIManager::Create(UI_ID id)
{
    CUI* ui = CreateClass(id);
    if (!ui) return nullptr;

    ui->Initialize();
    m_UIList.emplace_back(ui);

    SortList();

    return ui;
}

CUI* CUIManager::Create(UI_ID id, const vivid::Vector2& position)
{
    CUI* ui = CreateClass(id);

    if (!ui) return nullptr;

    ui->Initialize(position);
    m_UIList.emplace_back(ui);
    return ui;
}

CUI* CUIManager::Create(UI_ID id, const CVector3& position)
{
    CUI* ui = CreateClass(id);

    if (!ui) return nullptr;

    ui->Initialize(position);
    m_UIList.emplace_back(ui);

    return ui;
}

CUI* CUIManager::Create(UI_ID id, const CTransform& transform)
{
    CUI* ui = CreateClass(id);

    if (!ui) return nullptr;

    ui->Initialize(transform);
    m_UIList.emplace_back(ui);

    return ui;
}

void CUIManager::Delete(UI_ID id)
{
    if (m_UIList.empty()) return;

    UI_LIST::iterator it = m_UIList.begin();

    while (it != m_UIList.end())
    {
        CUI* ui = dynamic_cast<CUI*>((*it).get());


        if (ui->GetUI_ID() == id)
        {
            (*it)->SetActive(false);
        }

        ++it;
    }
}

CUIManager::UI_LIST CUIManager::GetList()
{
    return m_UIList;
}

void CUIManager::SortList(void)
{
    m_UIList.sort([](const CUI* p, const CUI* q) {return *p < *q; });
}

CUI* CUIManager::GetUI(UI_ID ui_id)
{
    if (m_UIList.empty()) return nullptr;

    UI_LIST::iterator it = m_UIList.begin();

    while (it != m_UIList.end())
    {
        CUI* ui = dynamic_cast<CUI*>((*it).get());


        if (ui->GetUI_ID() == ui_id)
        {
            return ui;
        }

        ++it;
    }
}

CUI* CUIManager::CreateClass(UI_ID id)
{
   std::shared_ptr<CUI> ui = nullptr;
    switch (id)
    {
    case UI_ID::PAUSE:
        ui = std::make_shared<CPause>(id);              break;
    case UI_ID::FALLOUT_TOPIC:
        ui = std::make_shared<CFallOutTopic>(id);       break;
    case UI_ID::FALLOUT_TOPIC_BG:
        ui = std::make_shared<CFalloutTopicBG>(id);     break;
    case UI_ID::TOPIC_SHUTTER:
        ui = std::make_shared<CTopicShutter>(id);       break;
    case UI_ID::PLANE_GAME_IMAGE:
        ui = std::make_shared<CPlaneGameImage>(id);     break;
    case UI_ID::MENU_BG:
        ui = std::make_shared<CMenuBG>(id);             break;
    case UI_ID::MENU_POSTER:
        ui = std::make_shared<CMenuPoster>(id);         break;
    case UI_ID::SCENE_TITLE:
        ui = std::make_shared<CSceneTitle>(id);         break;
    case UI_ID::PLAYER_NUM_SELECT:
        ui = std::make_shared<CPlayerNumSelect>(id);    break;
    case UI_ID::SKILL_ICON:
        ui = std::make_shared<CSkillIcon>(id);          break;
    case UI_ID::SKILL_GAUGE:
        ui = std::make_shared<CSkillGauge>(id);         break;
    case UI_ID::SKILL_CURSOR:
        ui = std::make_shared<CSkillCursor>(id);        break;
    case UI_ID::SKILL_NAME:
        ui = std::make_shared<CSkillName>(id);          break;
    case UI_ID::SKILL_INFO:
        ui = std::make_shared<CSkillInfomation>(id);    break;
    case UI_ID::SKILL_VIDEO:
        ui = std::make_shared<CSkillVideo>(id);         break;
    case UI_ID::FINISH_GAME_BG:
        ui = std::make_shared<CFinishGameBG>(id);       break;
    case UI_ID::TITLE_LOGO:
        ui = std::make_shared<CTitleLogo>(id);          break;
    case UI_ID::START_COUNTDOWN:
        ui = std::make_shared<CStartGameCount>(id);     break;
    case UI_ID::START_TEXT:
        ui = std::make_shared<CStartGameText>(id);      break;
    case UI_ID::FINISH_TEXT:
        ui = std::make_shared<CFinishGameText>(id);     break;
    case UI_ID::KEY:
        ui = std::make_shared<CKey>(id);                break;
    case UI_ID::KEY_BG:
        ui = std::make_shared<CKeyBG>(id);              break;
    case UI_ID::FADE:
        ui = std::make_shared<CFade>(id);               break;
    case UI_ID::GAME_BG:
        ui = std::make_shared<CGameBG>(id);             break;
    case UI_ID::SCENE_UI_PARENT:
        ui = std::make_shared<CSceneUIParent>(id);      break;
    case UI_ID::TITLE_BUTTON:
        ui = std::make_shared<CTitleButton>(id);        break;
    case UI_ID::GAME_VIDEO:
        ui = std::make_shared<CGameVideo>(id);          break;
    case UI_ID::MINIGAME_TITLE:
        ui = std::make_shared<CMiniGameTitle>(id);      break;
    case UI_ID::MINIGAME_MANUAL:
        ui = std::make_shared<CMiniGameManual>(id);     break;
    case UI_ID::MINIGAME_OVERVIEW:
        ui = std::make_shared<CMiniGameOverView>(id);   break;
    case UI_ID::PLAYER_READY:
        ui = std::make_shared<CPlayerReady>(id);        break;
    case UI_ID::NOTICE:
        ui = std::make_shared<CNotice>(id);             break;
    case UI_ID::NOTICE_WIDE:
        ui = std::make_shared<CNoticeWide>(id);         break;
    case UI_ID::TEXT_MANUAL:
        ui = std::make_shared<CTextManual>(id);         break;
    case UI_ID::TEXT_OVERVIEW:
        ui = std::make_shared<CTextOverview>(id);       break;
    case UI_ID::PLAYER_ICON:
        ui = std::make_shared<CPlayerIcon>(id);         break;
    case UI_ID::CONCENTRATION_LINE:
        ui = std::make_shared<CConcentrationLine>(id);  break;
    case UI_ID::RESULT_WINNER:
        ui = std::make_shared<CResultWinner>(id);       break;
    case UI_ID::ENTRY_X_BUTTON:
        ui = std::make_shared<CEntryXButton>(id);       break;
    case UI_ID::PLAYER_JOIN:
        ui = std::make_shared<CPlayerJoin>(id);         break;
    }

    return dynamic_cast<CUI*>(ui.get());
}

/*
 *  コンストラクタ
 */
CUIManager::
CUIManager(void)
{
}

/*
 *  コピーコンストラクタ
 */
CUIManager::
CUIManager(const CUIManager& rhs)
{
    (void)rhs;
}

/*
 *  デストラクタ
 */
CUIManager::
~CUIManager(void)
{
}


/*
 *  代入演算子
 */
CUIManager&
CUIManager::
operator=(const CUIManager& rhs)
{
    (void)rhs;

    return *this;
}
