#include "unit_manager.h"
#include "..\scene_manager\scene_manager.h"
#include "..\bullet_manager\bullet_manager.h"
#include "..\effect_manager\effect_manager.h"
#include "..\sound_manager\sound_manager.h"
#include "..\data_manager\data_manager.h"
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

        delete (*it);

        ++it;
    }

    m_UnitList.clear();
}

/*
 *  ���j�b�g����
 */
IUnit*
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
    

    if (!unit) return nullptr;

    unit->Initialize(id, pos, m_file_name_list[(int)id], m_controller_list[(int)id]);

    m_UnitList.push_back(unit);
    return unit;
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
        IUnit* unit = (IUnit*)(*it);

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
            return;
        IUnit* unit = (*it);
        //���������̔���-----------------------------------------------------
        float radius = unit->GetRadius();
        const int check_point_count = 4;
        for (int i = 0; i < 9; ++i)
        {
            CVector3 unit_pos = unit->GetPosition();
            CVector3 start = unit_pos + CVector3(( -radius / 2.0f) + (radius) * (i % 3), 0.0f, ( -radius / 2.0f) + (radius) * (i / 3));
            CheckHitObjectVertical(object, (*it), start, CVector3(0.0f, -radius*2, 0.0f));
        }
        
        //���������̔���-----------------------------------------------------
        if ((*it)->GetVelocity().x != 0 || (*it)->GetVelocity().z != 0)
        {
            //�ړ������̐���
            CVector3 startPos, endPos;
            startPos = (*it)->GetPosition();
            endPos = startPos;
            CVector3 tempVelocity = (*it)->GetVelocity().Normalize();
            endPos += tempVelocity * (*it)->GetRadius();
            CheckHitObjectHorizontal(object, (*it), startPos, endPos);

            
            //�ړ������̉E��45��
            startPos = (*it)->GetPosition();
            endPos = startPos;
            tempVelocity = (*it)->GetVelocity().RotateAroundCoordinatesAxis(COORDINATES_AXIS::Y, 45.0f).Normalize();
            endPos += tempVelocity * (*it)->GetRadius();
            CheckHitObjectHorizontal(object, (*it), startPos, endPos);


            //�ړ������̍���45��
            startPos = (*it)->GetPosition();
            endPos = startPos;
            tempVelocity = (*it)->GetVelocity().RotateAroundCoordinatesAxis(COORDINATES_AXIS::Y, -45.0f).Normalize();
            endPos += tempVelocity * (*it)->GetRadius();
            CheckHitObjectHorizontal(object, (*it), startPos, endPos);
        }

        ++it;
    }
    return;
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
 *  ���j�b�g�ƃX�e�[�W�Ƃ̃A�^������̏����i�����j
 */
void
CUnitManager::
CheckHitObjectVertical(IObject* object, IUnit* unit, const CVector3& startPos, const CVector3& down_dir, float length)
{
    CVector3 hitPos;
    CVector3 end_position = startPos + (down_dir * length);
#ifdef VIVID_DEBUG

    // �����̕`��
    DrawLine3D(startPos, end_position, GetColor(255, 255, 0));

#endif // VIVID_DEBUG
    if (object->GetModel().CheckHitLine(startPos, end_position) == true)
    {

        hitPos = object->GetModel().GetHitLinePosition(startPos, end_position);

        float diffHeight = hitPos.y - end_position.y;

        CVector3 unitPos = unit->GetPosition();
        unitPos.y += diffHeight;
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

    // �����̕`��
    //DrawLine3D(startPos, endPos, GetColor(255, 255, 0));

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