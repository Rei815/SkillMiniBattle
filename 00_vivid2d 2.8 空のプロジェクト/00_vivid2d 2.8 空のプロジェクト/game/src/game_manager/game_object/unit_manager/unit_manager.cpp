#include "unit_manager.h"
#include "..\scene_manager\scene_manager.h"
#include "..\bullet_manager\bullet_manager.h"
#include "..\effect_manager\effect_manager.h"
#include "..\sound_manager\sound_manager.h"
#include "..\data_manager\data_manager.h"
#include "..\..\..\utility\utility.h"
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

        ++it;
    }

    m_UnitList.clear();
}

/*
 *  ���j�b�g����
 */
std::shared_ptr<IUnit>
CUnitManager::
Create(UNIT_ID id, const CVector3& pos)
{
    std::shared_ptr<IUnit> unit = nullptr;

    switch (id)
    {
    case UNIT_ID::PLAYER1:
    case UNIT_ID::PLAYER2:
    case UNIT_ID::PLAYER3:
    case UNIT_ID::PLAYER4:
        unit = std::make_shared<CPlayer>();  break;
    }
    

    if (!unit) return nullptr;

    unit->Initialize(id, pos);

    m_UnitList.emplace_back(unit);
    return unit;
}

void CUnitManager::Delete(UNIT_ID id)
{
    if (m_UnitList.empty()) return;

    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {
        std::shared_ptr<IUnit> unit = *it;
        if (unit->GetUnitID() == id)
        {
            unit->Delete();
            return;
        }
        ++it;

    }
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
        std::shared_ptr<IUnit> unit = *it;

        if (bullet->GetColliderID() == COLLIDER_ID::MODEL)
            unit->CheckHitBulletModel(bullet);
        else
            unit->CheckHitBullet(bullet);

        ++it;
    }
}

/*
* �I�u�W�F�N�g�Ƃ̓����蔻��
*/
void CUnitManager::CheckHitObject(IObject* object)
{
    if (m_UnitList.empty()) return;
    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {
        if (object->GetModel().GetModelHandle() == VIVID_DX_ERROR || object->GetColliderActiveFlag() == false)
        {
            ++it;
            continue;
        }
        std::shared_ptr<IUnit> unit = *it;

        //���������̔���-----------------------------------------------------        
        
        CVector3 startPos, endPos, ForwardVector, CheckVector;

        //���ʕ����̎擾
        startPos = (*it)->GetPosition();
        ForwardVector = (*it)->GetForwardVector();
        ForwardVector.y = 0.0f;
        ForwardVector = CVector3().Normalize(ForwardVector);

        //���肷��i45�x������8�������`�F�b�N�j
        for (int i = 0; i < 8; i++)
        {
            endPos = startPos;
            CheckVector = ForwardVector.RotateAroundCoordinatesAxis(COORDINATES_AXIS::Y, 45.0f * i).Normalize();
            endPos += CheckVector * (*it)->GetRadius();
            CheckHitObjectHorizontal(object, unit.get(), startPos, endPos);
            DrawLine3D(startPos, endPos, 0xffffffff);
        }

        //���������̔���-----------------------------------------------------
        float radius = unit->GetRadius();
        float offset = radius / 2.0f;

        //���ォ��E���܂Ń`�F�b�N
        for (int i = 0; i < 9; ++i)
        {
            CVector3 unit_pos = unit->GetPosition();
            CVector3 start = unit_pos + CVector3(-offset + (offset) * (i % 3), 0.0f, -offset + (offset) * (i / 3));
            CheckHitObjectVertical(object, unit.get(), start, CVector3(0.0f, -radius * 3, 0.0f));
        }

        ++it;
    }

    return;
}


std::shared_ptr<CPlayer> CUnitManager::GetPlayer(UNIT_ID id)
{
    if (m_UnitList.empty()) return nullptr;

    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {
        if ((*it)->GetUnitID() == id)
            return dynamic_pointer_cast<CPlayer>(*it);

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
            std::shared_ptr<CPlayer> player = dynamic_pointer_cast<CPlayer>(*it);
            player->SetActionFlag(flag);
        }

        ++it;
    }

    return;

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


CUnitManager::UNIT_LIST CUnitManager::GetUnitList()
{
    return m_UnitList;
}

CUnitManager::DEFEAT_LIST CUnitManager::GetDefeatList()
{
    return m_DefeatList;
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
        std::shared_ptr<IUnit> unit = *it;

         unit->Update();

        if (!unit->IsActive())
        {
            unit->Finalize();

            it = m_UnitList.erase(it);

            continue;
        }

        ++it;
    }
}
/*
 *  ���j�b�g�ƃX�e�[�W�Ƃ̃A�^������̏����i�����j
 */
void
CUnitManager::
CheckHitObjectVertical(IObject* object, IUnit* unit, const CVector3& startPos, const CVector3& down_dir, float length)
{
    CVector3 hitPos;
    CVector3 end_position = startPos + (down_dir * length);

    //������
    if (object->GetModel().CheckHitLine(startPos, end_position) == true)
    {

        hitPos = object->GetModel().GetHitLinePosition(startPos, end_position);
        float footPos = 0.0f;
        footPos = unit->GetPosition().y - (unit->GetHeight() / 2.0f);

        if (hitPos.y < footPos) return;

        float diffHeight = 0.0f;
        diffHeight = hitPos.y - footPos;

        CVector3 unitPos = unit->GetPosition();
        unitPos.y += diffHeight;
        unit->SetPosition(unitPos);
    }

    //�����
    end_position = startPos + (-down_dir * length);
    if (object->GetModel().CheckHitLine(startPos, end_position) == true)
    {

        hitPos = object->GetModel().GetHitLinePosition(startPos, end_position);
        float headPos = unit->GetPosition().y + unit->GetHeight() / 2.0f;


        if (hitPos.y > headPos) return;

        float diffHeight = headPos - hitPos.y;

        CVector3 unitPos = unit->GetPosition();
        unitPos.y -= diffHeight;
        unit->SetPosition(unitPos);
    }
}

/*
 *  @brief      ���j�b�g�ƃX�e�[�W�Ƃ̃A�^������̏����i�����j
 */
void
CUnitManager::
CheckHitObjectHorizontal(IObject* object, IUnit* unit, const CVector3& startPos, const CVector3& endPos)
{
    CVector3 hitPos;

    if (object->GetModel().CheckHitLine(startPos, endPos) == true)
    {

        hitPos = object->GetModel().GetHitLinePosition(startPos, endPos);

        float diffX = endPos.x - hitPos.x;
        float diffZ = endPos.z - hitPos.z;

        CVector3 unitPos = unit->GetPosition();
        unitPos.x -= diffX;
        unitPos.z -= diffZ;
        unit->SetPosition(unitPos);
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