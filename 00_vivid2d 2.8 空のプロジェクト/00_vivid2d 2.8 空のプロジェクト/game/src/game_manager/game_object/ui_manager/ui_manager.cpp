#include "ui_manager.h"
#include "ui/boss_life/boss_life.h"
#include "ui/reticle/reticle.h"
#include "ui/pause/pause.h"
#include "ui/fall_select/fall_select.h"
 /*
  *  �C���X�^���X�̎擾
  */
CUIManager&
CUIManager::
GetInstance(void)
{
    static CUIManager instance;

    return instance;
}

/*
 *  ������
 */
void
CUIManager::
Initialize(void)
{
    m_UIList.clear();
}

/*
 *  �X�V
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
 *  �`��
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
 *  ���
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

void CUIManager::Create(UI_ID id)
{
    CUI* ui = nullptr;

    switch (id)
    {
    case UI_ID::PAUSE:          ui = new CPause();          break;
        break;
    }
    if (!ui) return;

    ui->Initialize();
    m_UIList.push_back(ui);

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

/*
 *  �R���X�g���N�^
 */
CUIManager::
CUIManager(void)
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
CUIManager::
CUIManager(const CUIManager& rhs)
{
    (void)rhs;
}

/*
 *  �f�X�g���N�^
 */
CUIManager::
~CUIManager(void)
{
}

/*
 *  ������Z�q
 */
CUIManager&
CUIManager::
operator=(const CUIManager& rhs)
{
    (void)rhs;

    return *this;
}
