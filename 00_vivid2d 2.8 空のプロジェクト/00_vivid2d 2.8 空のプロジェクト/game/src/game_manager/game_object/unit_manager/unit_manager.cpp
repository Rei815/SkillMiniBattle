#include "unit_manager.h"
#include "..\scene_manager\scene_manager.h"
#include "..\bullet_manager\bullet_manager.h"
#include "..\effect_manager\effect_manager.h"
#include "..\sound_manager\sound_manager.h"
#include "..\..\..\utility\utility.h"
#include "../ui_manager/ui_manager.h"

const std::string   CUnitManager::m_file_name_list[] = { "data\\Models\\player.mv1", "data\\Models\\player.mv1" };
const int           CUnitManager::m_controller_list[] = { DX_INPUT_PAD1, DX_INPUT_PAD2,DX_INPUT_PAD3,DX_INPUT_PAD4 };
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

    unit->Initialize(pos, m_file_name_list[(int)id], m_controller_list[(int)id]);
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

        DxLib::MV1_COLL_RESULT_POLY_DIM hit_poly_dim = MV1CollCheck_LineDim(object->GetModel().GetModelHandle(), -1, startPos, endPos, -1);

        // �����̕`��
        DrawLine3D(startPos, endPos, GetColor(255, 255, 0));

        if (hit_poly_dim.HitNum >= 1)
        {
            if (object->GetTag() == "Fall")
            (*it)->SetIsGround(true);
            for (int i = 0; i < hit_poly_dim.HitNum; i++)
            {
                MV1_COLL_RESULT_POLY* pCollResultPoly = &hit_poly_dim.Dim[i];

                float diffHeight = endPos.y - pCollResultPoly->HitPosition.y;

                CVector3 unitPos = (*it)->GetPosition();
                unitPos.y -= diffHeight;
                (*it)->SetPosition(unitPos);

            }
        }



        // �����蔻����̌�n��
        MV1CollResultPolyDimTerminate(hit_poly_dim);

        ++it;
    }

}

CPlayer* CUnitManager::GetPlayer(void)
{
    if (m_UnitList.empty()) return nullptr;

    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {
        if ((*it)->GetUnitID() == UNIT_ID::PLAYER1)
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