#include "gimmick_manager.h"
#include "gimmick/fall_gimmick/fall_gimmick.h"
/*
 *  インスタンスの取得
 */
CGimmickManager&
CGimmickManager::
GetInstance(void)
{
    static CGimmickManager instance;

    return instance;
}

/*
 *  初期化
 */
void
CGimmickManager::
Initialize(void)
{

}

/*
 *  更新
 */
void
CGimmickManager::Update(void)
{
    if (m_GimmickList.empty()) return;

    GIMMICK_LIST::iterator it = m_GimmickList.begin();

    while (it != m_GimmickList.end())
    {
        CG* ui = (CUI*)(*it);

        ui->Update();

        if (!ui->GetActive())
        {
            ui->Finalize();

            delete ui;

            it = m_GimmickList.erase(it);

            continue;
        }

        ++it;
    }

}

/*
 *  描画
 */
void CGimmickManager::Draw(void)
{
    if (m_GimmickList.empty()) return;

    GIMMICK_LIST::iterator it = m_GimmickList.begin();

    while (it != m_GimmickList.end())
    {
        (*it)->Draw();

        ++it;
    }
}

/*
 *  解放
 */
void CGimmickManager::Finalize(void)
{
    if (m_GimmickList.empty()) return;

    GIMMICK_LIST::iterator it = m_GimmickList.begin();

    while (it != m_GimmickList.end())
    {
        (*it)->Finalize();

        delete (*it);

        ++it;
    }

    m_GimmickList.clear();
}

void CGimmickManager::Create(UI_ID id)
{
    CUI* ui = nullptr;

    switch (id)
    {
    case UI_ID::PLAYER_LIFE:    ui = new CPlayerLife();     break;
    case UI_ID::BOSS_LIFE:      ui = new CBossLife();     break;
    case UI_ID::RETICLE:        ui = new CReticle();        break;
    case UI_ID::PAUSE:          ui = new CPause();          break;
        break;
    }
    if (!ui) return;

    ui->Initialize();
    m_GimmickList.push_back(ui);

}

void CGimmickManager::Delete(UI_ID id)
{
    if (m_GimmickList.empty()) return;

    GIMMICK_LIST::iterator it = m_GimmickList.begin();

    while (it != m_GimmickList.end())
    {
        CUI* ui = (CUI*)(*it);


        if (ui->GetUI_ID() == id)
        {
            (*it)->SetActive(false);
        }

        ++it;
    }
}

bool CGimmickManager::CheckUIAttribute(CUI::UI_ATTRIBUTE ui_attribute)
{
    if (m_GimmickList.empty()) return false;

    GIMMICK_LIST::iterator it = m_GimmickList.begin();

    while (it != m_GimmickList.end())
    {
        CUI* ui = (CUI*)(*it);


        if (ui->CheckAttribute(ui_attribute) == true)
            return true;

        ++it;
    }
    return false;
}

bool CGimmickManager::GetReceivedReward(void)
{
    return m_ReceivedReward;
}

void CGimmickManager::SetReceivedReward(bool active)
{
    m_ReceivedReward = active;
}

bool CGimmickManager::GetWaveClearUIActive(void)
{
    return m_WaveClearUIActiveFlag;
}

void CGimmickManager::SetWaveClearUIActive(bool active)
{
    m_WaveClearUIActiveFlag = active;
}

int CGimmickManager::GetUIActive(UI_ID ui_id)
{
    if (m_GimmickList.empty()) return -1;

    GIMMICK_LIST::iterator it = m_GimmickList.begin();

    while (it != m_GimmickList.end())
    {
        CUI* ui = (CUI*)(*it);


        if (ui->GetUI_ID() == ui_id && ui->GetActive() != false)
            return 1;

        if (ui->GetUI_ID() == ui_id && ui->GetActive() != true)
            return 0;
        ++it;
    }
    return -1;
}

void CGimmickManager::Create(GIMMICK_ID id)
{
}

/*
 *  コンストラクタ
 */
CGimmickManager::
CGimmickManager(void)
{
}

/*
 *  コピーコンストラクタ
 */
CGimmickManager::
CGimmickManager(const CGimmickManager& rhs)
{
    (void)rhs;
}

/*
 *  デストラクタ
 */
CGimmickManager::
~CGimmickManager(void)
{
}

/*
 *  代入演算子
 */
CGimmickManager&
CGimmickManager::
operator=(const CGimmickManager& rhs)
{
    (void)rhs;

    return *this;
}
