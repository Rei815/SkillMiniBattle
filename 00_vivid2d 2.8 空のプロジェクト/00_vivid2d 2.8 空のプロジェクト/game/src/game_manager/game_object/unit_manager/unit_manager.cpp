#include "unit_manager.h"
#include "..\scene_manager\scene_manager.h"
#include "..\bullet_manager\bullet_manager.h"
#include "..\effect_manager\effect_manager.h"
#include "..\sound_manager\sound_manager.h"
#include "..\..\..\utility\utility.h"
#include "unit\player\player_1\player_1.h"
#include "unit\player\player_2\player_2.h"
#include "../ui_manager/ui_manager.h"


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

    CheckHitStage();

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
Create(UNIT_ID id, const CVector3& pos, MOVE_ID moveId, bool aimFlag)
{
    IUnit* unit = nullptr;

    switch (id)
    {
    case UNIT_ID::PLAYER1:              unit = new CPlayer1();      break;
    case UNIT_ID::PLAYER2:              unit = new CPlayer2();      break;
    case UNIT_ID::PLAYER3:              unit = new CPlayer1();      break;
    case UNIT_ID::PLAYER4:              unit = new CPlayer1();      break;
    }

    if (!unit) return;

    unit->Initialize(pos, moveId);
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

void CUnitManager::CheckHitStage()
{
    if (m_UnitList.empty()) return;
    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {

        if (CStage::GetInstance().GetModel().GetModelHandle() == VIVID_DX_ERROR)
            return;

        CVector3 startPos = (*it)->GetPosition();
        CVector3 dir = (*it)->GetVelocity().Normalize();

        //�����Ă���ꍇ���1��-1��ۂ�
        dir.x = (dir.x > 0) - (dir.x < 0);

        CVector3 endPos = startPos + dir * (*it)->GetRadius();

        DxLib::MV1_COLL_RESULT_POLY_DIM hit_poly_dim = MV1CollCheck_LineDim(CStage::GetInstance().GetModel().GetModelHandle(), -1, startPos, endPos);

        // �����̕`��
        DrawLine3D(startPos, endPos, GetColor(255, 255, 0));

        if (hit_poly_dim.HitNum >= 1)
        {

            (*it)->SetVelocity(CVector3::ZERO);

            CVector3 hitPos = CVector3(hit_poly_dim.Dim->HitPosition.x, hit_poly_dim.Dim->HitPosition.y, hit_poly_dim.Dim->HitPosition.z);

            CVector3 diffPos = endPos - hitPos;

            if (diffPos != CVector3::ZERO)
                (*it)->SetPosition((*it)->GetPosition() - diffPos);
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