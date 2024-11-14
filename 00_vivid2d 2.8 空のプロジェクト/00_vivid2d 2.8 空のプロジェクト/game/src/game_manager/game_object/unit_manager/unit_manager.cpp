#include "unit_manager.h"
#include "..\scene_manager\scene_manager.h"
#include "..\bullet_manager\bullet_manager.h"
#include "..\effect_manager\effect_manager.h"
#include "..\sound_manager\sound_manager.h"
#include "..\..\..\utility\utility.h"
#include "../ui_manager/ui_manager.h"

const std::string   CUnitManager::m_file_name_list[] = { "data\\Models\\player.mv1", "data\\Models\\player.mv1", "data\\Models\\player.mv1", "data\\Models\\player.mv1" };
const vivid::controller::DEVICE_ID           CUnitManager::m_controller_list[] = { vivid::controller::DEVICE_ID::PLAYER1 , vivid::controller::DEVICE_ID::PLAYER2,vivid::controller::DEVICE_ID::PLAYER3,vivid::controller::DEVICE_ID::PLAYER4 };
/*
 *  �C���X�^���X�̎擾
 */
CUnitManager&
CUnitManager::
GetInstance(void)
{
    static CUnitManager instance;

    return instance;
}

/*
 *  ������
 */
void
CUnitManager::
Initialize(void)
{
    m_UnitList.clear();
    m_RankingList.clear();
    m_DefeatList.clear();
}

/*
 *  �X�V
 */
void
CUnitManager::
Update(void)
{

    // ���j�b�g�X�V
    UpdateUnit();

    CheckDefeat();
}

/*
 *  �`��
 */
void
CUnitManager::
Draw(void)
{
    if (m_UnitList.empty()) return;

    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {
        (*it)->Draw();

        ++it;
    }
}

/*
 *  ���
 */
void
CUnitManager::
Finalize(void)
{
    if (m_UnitList.empty()) return;

    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {
        (*it)->Finalize();

        delete (*it);

        ++it;
    }

    m_UnitList.clear();
}

/*
 *  ���j�b�g����
 */
void
CUnitManager::
Create(UNIT_ID id, const CVector3& pos)
{
    IUnit* unit = nullptr;

    std::string fileName = m_file_name_list[(int)id];
    switch (id)
    {
    case UNIT_ID::PLAYER1:
    case UNIT_ID::PLAYER2:
    case UNIT_ID::PLAYER3:
    case UNIT_ID::PLAYER4:
    unit = new CPlayer();  break;
    }
    

    if (!unit) return;

    unit->Initialize(id, pos, m_file_name_list[(int)id], m_controller_list[(int)id]);
    m_UnitList.push_back(unit);
}

/*
 *  ���j�b�g�ƒe�̃A�^������
 */
void
CUnitManager::
CheckHitBullet(IBullet* bullet)
{
    if (m_UnitList.empty()) return;

    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {

        if ((*it)->CheckHitBullet(bullet))
            return;

        ++it;
    }
}

void CUnitManager::CheckHitObject(IObject* object)
{
    if (m_UnitList.empty()) return;
    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {

        if (object->GetModel().GetModelHandle() == VIVID_DX_ERROR)
            return;

        CVector3 startPos = (*it)->GetPosition();
        startPos.y += (*it)->GetRadius();

        CVector3 endPos = (*it)->GetPosition();
        endPos.y -= (*it)->GetRadius();

        CVector3 hitPos;

        // �����̕`��
        DrawLine3D(startPos, endPos, GetColor(255, 255, 0));

        if (object->GetModel().CheckHitLine(startPos, endPos) == true)
        {

            hitPos = object->GetModel().GetHitLinePosition(startPos, endPos);

            (*it)->SetIsGround(true);
            float diffHeight = endPos.y - hitPos.y;

            CVector3 unitPos = (*it)->GetPosition();
            unitPos.y -= diffHeight;
            (*it)->SetPosition(unitPos);
        }

        ++it;
    }

}


CPlayer* CUnitManager::GetPlayer(UNIT_ID id)
{
    if (m_UnitList.empty()) return nullptr;

    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {
        if ((*it)->GetUnitID() == id)
            return (CPlayer*)(*it);

        ++it;
    }

    return nullptr;
}

void CUnitManager::SetAllPlayerAction(bool flag)
{
    if (m_UnitList.empty()) return;

    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {
        if ((*it)->GetUnitCategory() == UNIT_CATEGORY::PLAYER)
        {
            CPlayer* player = (CPlayer*)(*it);
            player->SetActionFlag(flag);
        }

        ++it;
    }

    return;

}

CVector3 CUnitManager::CheckHitLine(const CVector3& startPos, const CVector3& endPos)
{
    CVector3 hitPos = CStage::GetInstance().GetModel().GetHitLinePosition(startPos, endPos);
    if (m_UnitList.empty()) return hitPos;
    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {
        if ((*it)->GetModel().CheckHitLine(startPos, endPos) == true)
            hitPos = (*it)->GetModel().GetHitLinePosition(startPos, endPos);

        ++it;
    }
    return hitPos;
}

bool CUnitManager::CheckHitLineEnemy(const CVector3& startPos, const CVector3& endPos)
{
    if (m_UnitList.empty()) return false;
    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {
        if ((*it)->GetModel().CheckHitLine(startPos, endPos) == true && (*it)->GetUnitCategory() != UNIT_CATEGORY::PLAYER)
            return true;

        ++it;
    }

    return false;
}

int CUnitManager::GetCurrentPlayer()
{
    return m_CurrentPlayerNum;
}

CUnitManager::UNIT_LIST CUnitManager::GetUnitList()
{
    return m_UnitList;
}

CUnitManager::DEFEAT_LIST CUnitManager::GetDefeatList()
{
    return m_DefeatList;
}

void CUnitManager::SetCurrentPlayer(int num)
{
    if (num > 4 || num < 1) return;
    m_CurrentPlayerNum = num;
}

/*
 *  ���j�b�g�X�V
 */
void
CUnitManager::
UpdateUnit(void)
{
    if (m_UnitList.empty()) return;

    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {
        IUnit* unit = (IUnit*)(*it);

        unit->Update();

        if (!unit->GetActive())
        {
            unit->Finalize();

            delete unit;

            it = m_UnitList.erase(it);

            continue;
        }

        ++it;
    }
}

void CUnitManager::CheckDefeat()
{
    if (m_UnitList.empty()) return;

    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {
        if ((*it)->GetDefeatFlag())
        {
            if (m_DefeatList.empty())
            {
                m_DefeatList.push_back((*it));
                return;
            }

            bool checkFlag = false;
            //2��ڂ͓���Ȃ��悤��
            for (DEFEAT_LIST::iterator i = m_DefeatList.begin(); i != m_DefeatList.end(); i++)
            {
                if ((*it)->GetUnitID() == (*i)->GetUnitID())
                {
                    checkFlag = true;
                    break;
                }
            }

            if (!checkFlag)
                m_DefeatList.push_back((*it));

            //�Ō�̈�l����ʂƂ��ď���
            if (m_DefeatList.size() == m_CurrentPlayerNum - 1)
            {
                UNIT_LIST::iterator it = m_UnitList.begin();

                while (it != m_UnitList.end())
                {
                    bool checkFlag = true;
                    for (DEFEAT_LIST::iterator i = m_DefeatList.begin(); i != m_DefeatList.end(); i++)
                    {
                        if ((*it)->GetUnitID() == (*i)->GetUnitID())
                        {
                            checkFlag = false;
                            break;
                        }
                    }
                    if (checkFlag)
                    {
                        CPlayer* player = GetPlayer((*it)->GetUnitID());
                        player->AddWins();
                    }

                    ++it;
                }
            }

        }

        ++it;
    }
}


/*
 *  �R���X�g���N�^
 */
CUnitManager::
CUnitManager(void)
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
CUnitManager::
CUnitManager(const CUnitManager& rhs)
{
    (void)rhs;
}

/*
 *  �f�X�g���N�^
 */
CUnitManager::
~CUnitManager(void)
{
}

/*
 *  ������Z�q
 */
CUnitManager&
CUnitManager::
operator=(const CUnitManager& rhs)
{
    (void)rhs;

    return *this;
}