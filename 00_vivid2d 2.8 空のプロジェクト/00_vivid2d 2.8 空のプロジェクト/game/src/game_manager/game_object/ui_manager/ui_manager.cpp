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
        CUI* ui = static_cast<CUI*>(*it);
        if(ui->GetUI_ID() == UI_ID::PAUSE || !CSceneManager::GetInstance().Pausing())
            ui->Update();
        SortList();
        if (!ui->GetActive())
        {

            ui->Finalize();

            delete ui;
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

        delete (*it);
        ++it;
    }

    m_UIList.clear();
}

CUI* CUIManager::Create(UI_ID id)
{
    CUI* ui = CreateClass(id);
    if (!ui) return nullptr;

    ui->Initialize();
    m_UIList.push_back(ui);

    SortList();

    return ui;
}

CUI* CUIManager::Create(UI_ID id, const vivid::Vector2& position)
{
    CUI* ui = CreateClass(id);

    if (!ui) return nullptr;

    ui->Initialize(position);
    m_UIList.push_back(ui);
    return ui;
}

CUI* CUIManager::Create(UI_ID id, const CVector3& position)
{
    CUI* ui = CreateClass(id);

    if (!ui) return nullptr;

    ui->Initialize(position);
    m_UIList.push_back(ui);

    return ui;
}

CUI* CUIManager::Create(UI_ID id, const CTransform& transform)
{
    CUI* ui = CreateClass(id);

    if (!ui) return nullptr;

    ui->Initialize(transform);
    m_UIList.push_back(ui);

    return ui;
}

void CUIManager::Delete(UI_ID id)
{
    if (m_UIList.empty()) return;

    UI_LIST::iterator it = m_UIList.begin();

    while (it != m_UIList.end())
    {
        CUI* ui = (CUI*)(*it);


        if (ui->GetUI_ID() == id)
        {
            (*it)->SetActive(false);
        }

        ++it;
    }
}

void CUIManager::Delete(const CUI* ui_pointer)
{
    if (m_UIList.empty()) return;

    UI_LIST::iterator it = m_UIList.begin();

    while (it != m_UIList.end())
    {
        CUI* ui = (CUI*)(*it);


        if (ui == ui_pointer)
        {
            (*it)->SetActive(false);
        }

        ++it;
    }

}

int CUIManager::GetUIActive(UI_ID ui_id)
{
    if (m_UIList.empty()) return -1;

    UI_LIST::iterator it = m_UIList.begin();

    while (it != m_UIList.end())
    {
        CUI* ui = (CUI*)(*it);


        if (ui->GetUI_ID() == ui_id && ui->GetActive() != false)
            return 1;

        if(ui->GetUI_ID() == ui_id && ui->GetActive() != true)
            return 0;
        ++it;
    }
    return -1;
}

CUIManager::UI_LIST CUIManager::GetList()
{
    return m_UIList;
}

void CUIManager::SortList(void)
{
    m_UIList.sort([](const CUI* p, const CUI* q) {return *p < *q; });
}

/*
 *  指定のUIを返す
 */
CUI* CUIManager::GetUI(UI_ID ui_id)
{
    if (m_UIList.empty()) return nullptr;

    UI_LIST::iterator it = m_UIList.begin();

    while (it != m_UIList.end())
    {
        CUI* ui = (CUI*)(*it);


        if (ui->GetUI_ID() == ui_id)
        {
            return ui;
        }

        ++it;
    }
}

CUI* CUIManager::CreateClass(UI_ID id)
{
   CUI* ui = nullptr;
    switch (id)
    {
    case UI_ID::PAUSE:
        ui = new CPause(id);                break;
    case UI_ID::FALLOUT_TOPIC:
        ui = new CFallOutTopic(id);         break;
    case UI_ID::FALLOUT_TOPIC_BG:
        ui = new CFalloutTopicBG(id);       break;
    case UI_ID::TOPIC_SHUTTER:
        ui = new CTopicShutter(id);         break;
    case UI_ID::PLANE_GAME_IMAGE:
        ui = new CPlaneGameImage(id);       break;
    case UI_ID::MENU_BG:
        ui = new CMenuBG(id);               break;
    case UI_ID::MENU_POSTER:
        ui = new CMenuPoster(id);           break;
    case UI_ID::SCENE_TITLE:
        ui = new CSceneTitle(id);           break;
    case UI_ID::PLAYER_NUM_SELECT:
        ui = new CPlayerNumSelect(id);      break;
    case UI_ID::SKILL_ICON:
        ui = new CSkillIcon(id);            break;
    case UI_ID::SKILL_GAUGE:
        ui = new CSkillGauge(id);           break;
    case UI_ID::SKILL_CURSOR:
        ui = new CSkillCursor(id);          break;
    case UI_ID::SKILL_NAME:
        ui = new CSkillName(id);            break;
    case UI_ID::SKILL_INFO:
        ui = new CSkillInfomation(id);      break;
    case UI_ID::SKILL_VIDEO:
        ui = new CSkillVideo(id);           break;
    case UI_ID::FINISH_GAME_BG:
        ui = new CFinishGameBG(id);         break;
    case UI_ID::TITLE_LOGO:
        ui = new CTitleLogo(id);            break;
    case UI_ID::START_COUNTDOWN:
        ui = new CStartGameCount(id);       break;
    case UI_ID::START_TEXT:
        ui = new CStartGameText(id);        break;
    case UI_ID::FINISH_TEXT:
        ui = new CFinishGameText(id);       break;
    case UI_ID::KEY:
        ui = new CKey(id);                  break;
    case UI_ID::KEY_BG:
        ui = new CKeyBG(id);                break;
    case UI_ID::FADE:
        ui = new CFade(id);                 break;
    case UI_ID::GAME_BG:
        ui = new CGameBG(id);               break;
    case UI_ID::SCENE_UI_PARENT:
        ui = new CSceneUIParent(id);        break;
    case UI_ID::TITLE_BUTTON:
        ui = new CTitleButton(id);          break;
    case UI_ID::GAME_VIDEO:
        ui = new CGameVideo(id);            break;
    case UI_ID::MINIGAME_TITLE:
        ui = new CMiniGameTitle(id);        break;
    case UI_ID::MINIGAME_MANUAL:
        ui = new CMiniGameManual(id);       break;
    case UI_ID::MINIGAME_OVERVIEW:
        ui = new CMiniGameOverView(id);     break;
    case UI_ID::PLAYER_READY:
        ui = new CPlayerReady(id);          break;
    case UI_ID::NOTICE:
        ui = new CNotice(id);               break;
    case UI_ID::NOTICE_WIDE:
        ui = new CNoticeWide(id);           break;
    case UI_ID::TEXT_MANUAL:
        ui = new CTextManual(id);           break;
    case UI_ID::TEXT_OVERVIEW:
        ui = new CTextOverview(id);           break;
    case UI_ID::PLAYER_ICON:
        ui = new CPlayerIcon(id);           break;
    case UI_ID::CONCENTRATION_LINE:
        ui = new CConcentrationLine(id);           break;
    case UI_ID::RESULT_WINNER:
        ui = new CResultWinner(id);           break;
    case UI_ID::ENTRY_X_BUTTON:
        ui = new CEntryXButton(id);           break;
    case UI_ID::PLAYER_JOIN:
        ui = new CPlayerJoin(id);           break;
    }

    return ui;
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
