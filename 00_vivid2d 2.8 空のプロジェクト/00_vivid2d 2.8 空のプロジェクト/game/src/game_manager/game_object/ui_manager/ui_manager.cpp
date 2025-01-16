#include "ui_manager.h"
#include "ui/pause/pause.h"
#include "ui/fallout_topic/fallout_topic.h"
#include "ui/fallout_topic_bg/fallout_topic_bg.h"
#include "ui/topic_shutter/topic_shutter.h"
#include "ui/random_game/random_game.h"
#include "ui/finish_backGround/finish_backGround.h"
#include "ui/skill_icon/skill_icon.h"
#include "ui/skill_gauge/skill_gauge.h"
#include "ui/skill_cursor/skill_cursor.h"
#include "ui/key/key.h"
#include "ui/key_bg/key_bg.h"
#include "ui/title_logo/title_logo.h"
#include "ui/start_game_count/start_game_count.h"
#include "ui/start_game_text/start_game_text.h"
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
        CUI* ui = (CUI*)(*it);

        ui->Update();

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
    CUI* ui = nullptr;

    switch (id)
    {
    case UI_ID::PAUSE:
        ui = new CPause(id);          break;
    case UI_ID::FALLOUT_TOPIC:
        ui = new CFallOutTopic(id);   break;
    case UI_ID::RANDOM_GAME:
        ui = new CRandomGame(id);     break;
    case UI_ID::SKILL_ICON:
        ui = new CSkillIcon(id);      break;
    case UI_ID::SKILL_GAUGE:
        ui = new CSkillGauge(id);   break;
    case UI_ID::SKILL_CURSOR:
        ui = new CSkillCursor(id);    break;
    case UI_ID::FINISH_GAME_BG:
        ui = new CFinishGameBG(id);     break;
    case UI_ID::TITLE_LOGO:
        ui = new CTitleLogo(id);     break;
    case UI_ID::START_COUNTDOWN:
        ui = new CStartGameCount(id);     break;
    case UI_ID::START_TEXT:
        ui = new CStartGameText(id);    break;
    }
    if (!ui) return nullptr;

    ui->Initialize();
    m_UIList.push_back(ui);

    return ui;
}

CUI* CUIManager::Create(UI_ID id, const vivid::Vector2& position)
{
    CUI* ui = nullptr;

    switch (id)
    {
    case UI_ID::PAUSE:
        ui = new CPause(id);                break;
    case UI_ID::FALLOUT_TOPIC:
        ui = new CFallOutTopic(id);   break;
    case UI_ID::FALLOUT_TOPIC_BG:
        ui = new CFalloutTopicBG(id);   break;
    case UI_ID::TOPIC_SHUTTER:
        ui = new CTopicShutter(id);   break;
    case UI_ID::RANDOM_GAME:
        ui = new CRandomGame(id);           break;
    case UI_ID::SKILL_ICON:
        ui = new CSkillIcon(id);      break;
    case UI_ID::SKILL_GAUGE:
        ui = new CSkillGauge(id);   break;
    case UI_ID::SKILL_CURSOR:
        ui = new CSkillCursor(id);    break;
    case UI_ID::FINISH_GAME_BG:
        ui = new CFinishGameBG(id);     break;
    case UI_ID::KEY:
        ui = new CKey(id);     break;
    case UI_ID::KEY_BG:
        ui = new CKeyBG(id);     break;
        break;
    }

    if (!ui) return nullptr;

    ui->Initialize(position);
    m_UIList.push_back(ui);

    return ui;
}

CUI* CUIManager::Create(UI_ID id, const CVector3& position)
{
    CUI* ui = nullptr;

    switch (id)
    {
    case UI_ID::PAUSE:
        ui = new CPause(id);                break;
    case UI_ID::FALLOUT_TOPIC:
        ui = new CFallOutTopic(id);   break;
    case UI_ID::RANDOM_GAME:
        ui = new CRandomGame(id);           break;
    case UI_ID::SKILL_ICON:
        ui = new CSkillIcon(id);      break;
    case UI_ID::SKILL_GAUGE:
        ui = new CSkillGauge(id);   break;
    case UI_ID::SKILL_CURSOR:
        ui = new CSkillCursor(id);    break;
    case UI_ID::FINISH_GAME_BG:
        ui = new CFinishGameBG(id);     break;
    }

    if (!ui) return nullptr;

    ui->Initialize(position);
    m_UIList.push_back(ui);

    return ui;
}

CUI* CUIManager::Create(UI_ID id, const CTransform& transform)
{
    CUI* ui = nullptr;

    switch (id)
    {
    case UI_ID::PAUSE:
        ui = new CPause(id);          break;
    case UI_ID::FALLOUT_TOPIC:
        ui = new CFallOutTopic(id);   break;
    case UI_ID::RANDOM_GAME:
        ui = new CRandomGame(id);     break;
    case UI_ID::SKILL_ICON:
        ui = new CSkillIcon(id);      break;
    case UI_ID::SKILL_GAUGE:
        ui = new CSkillGauge(id);   break;
    case UI_ID::SKILL_CURSOR:
        ui = new CSkillCursor(id);    break;
    case UI_ID::FINISH_GAME_BG:
        ui = new CFinishGameBG(id);     break;
    }
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

bool CUIManager::CheckUIAttribute(CUI::UI_ATTRIBUTE ui_attribute)
{
    if (m_UIList.empty()) return false;

    UI_LIST::iterator it = m_UIList.begin();

    while (it != m_UIList.end())
    {
        CUI* ui = (CUI*)(*it);

        if (ui->CheckAttribute(ui_attribute) == true)
            return true;

        ++it;
    }
    return false;
}

bool CUIManager::GetReceivedReward(void)
{
    return m_ReceivedReward;
}

void CUIManager::SetReceivedReward(bool active)
{
    m_ReceivedReward = active;
}

bool CUIManager::GetWaveClearUIActive(void)
{
    return m_WaveClearUIActiveFlag;
}

void CUIManager::SetWaveClearUIActive(bool active)
{
    m_WaveClearUIActiveFlag = active;
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
