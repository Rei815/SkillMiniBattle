#include "object_manager.h"
#include "..\..\..\utility\utility.h"
#include "object\fall_object\fall_object.h"
#include "object\cannon_object\cannon_object.h"
#include "object\ogre_object\ogre_object.h"
#include "object\dodgeball_stage_object\dodgeball_stage_object.h"
#include "object\daruma_falldown_stage_object\daruma_falldown_stage_object.h"
#include "object\belt_conveyor_object\belt_conveyor_object.h"
#include "object\belt_conveyor_obstruction_object\belt_conveyor_obstruction_object.h"
#include "object\skill_wall_object\skill_wall_object.h"
#include "object\maze_stage\maze_stage.h"
#include "..\gimmick_manager\gimmick_manager.h"
#include "..\unit_manager\unit_manager.h"

/*
 *  �C���X�^���X�̎擾
 */
CObjectManager&
CObjectManager::
GetInstance(void)
{
    static CObjectManager instance;

    return instance;
}

/*
 *  ������
 */
void
CObjectManager::
Initialize(void)
{
    m_ObjectList.clear();
}

/*
 *  �X�V
 */
void
CObjectManager::
Update(void)
{
    // �I�u�W�F�N�g�X�V
    UpdateObject();

    OBJECT_LIST::iterator it = m_ObjectList.begin();

    while (it != m_ObjectList.end())
    {
        CUnitManager::GetInstance().CheckHitObject((*it));

        ++it;
    }
}

/*
 *  �`��
 */
void
CObjectManager::
Draw(void)
{
    if (m_ObjectList.empty()) return;

    OBJECT_LIST::iterator it = m_ObjectList.begin();

    while (it != m_ObjectList.end())
    {
        (*it)->Draw();

        ++it;
    }
}

/*
 *  ���
 */
void
CObjectManager::
Finalize(void)
{
    if (m_ObjectList.empty()) return;

    OBJECT_LIST::iterator it = m_ObjectList.begin();

    while (it != m_ObjectList.end())
    {
        (*it)->Finalize();

        delete (*it);

        ++it;
    }

    m_ObjectList.clear();
}

/*
 *  �I�u�W�F�N�g����
 */
IObject*
CObjectManager::
Create(OBJECT_ID id, const CTransform& transform)
{
    IObject* object = nullptr;

    switch (id)
    {

    case OBJECT_ID::MOON_FALL_OBJECT:
    case OBJECT_ID::SUN_FALL_OBJECT:
    case OBJECT_ID::CIRCLE_FALL_OBJECT:
    case OBJECT_ID::SQUARE_FALL_OBJECT:
    case OBJECT_ID::TRIANGLE_FALL_OBJECT:
    case OBJECT_ID::CROSS_FALL_OBJECT:
        object = new CFallObject();      break;
    case OBJECT_ID::CANNON_OBJECT:
        object = new CCannonObject();   break;
    case OBJECT_ID::OGRE_OBJECT:
        object = new COgreObject();     break;
    case OBJECT_ID::DODGEBALL_STAGE_OBJECT:
        object = new CDogeballStageObject(); break;
    case OBJECT_ID::DARUMA_FALLDOWN_STAGE_OBJECT:
        object = new CDarumaFallDownStageObject(); break;
    case OBJECT_ID::BELT_CONVEYOR_STAGE_OBJECT:
        object = new CBeltConveyorObject(); break;
    case OBJECT_ID::BELT_CONVEYOR_OBSTRUCTION_OBJECT:
        object = new CBeltConveyorObstructionObject(); break;
    case OBJECT_ID::SKILL_WALL_OBJECT:
        object = new CSkillWallObject(); break;
    case OBJECT_ID::MAZE_STAGE:
        object = new CMazeStage(); break;
    }

    if (!object) return nullptr;

    object->Initialize(id, transform);
    m_ObjectList.push_back(object);

    return object;
}

void CObjectManager::StartGimmick(GIMMICK_ID gimmick_id, IObject* object)
{
    if (m_ObjectList.empty()) return;

    CGimmickManager::GetInstance().Create(gimmick_id, object);
}

void CObjectManager::StartGimmick(GIMMICK_ID gimmick_id, IObject* object, float time)
{
    if (m_ObjectList.empty()) return;

    CGimmickManager::GetInstance().Create(gimmick_id, object, time);

}

CObjectManager::OBJECT_LIST CObjectManager::GetList()
{
    return m_ObjectList;
}

/*
* ���������I�u�W�F�N�g��Ԃ�
*/
IObject* CObjectManager::CheckHitObject(CPlayer* player)
{
    if (m_ObjectList.empty()) return nullptr;
    OBJECT_LIST::iterator it = m_ObjectList.begin();

    while (it != m_ObjectList.end())
    {

        if ((*it)->GetModel().GetModelHandle() == VIVID_DX_ERROR || (*it)->GetColliderActiveFlag() == false)
        {
            ++it;
            continue;
        }

        //���������̔���-----------------------------------------------------

        float radius = player->GetRadius();
        float offset = radius / 2.0f;
        for (int i = 0; i < 9; ++i)
        {
            CVector3 unit_pos = player->GetPosition();

            CVector3 start = unit_pos + CVector3(-offset + (offset) * (i % 3), 0.0, -offset + (offset) * (i / 3));
            CVector3 end_position = start + CVector3(0, -radius, 0);

            if ((*it)->GetModel().CheckHitLine(start, end_position) == true)
                return (*it);
        }

        ++it;
    }
    return nullptr;
}

/*
 *  �I�u�W�F�N�g�X�V
 */
void
CObjectManager::
UpdateObject(void)
{
    if (m_ObjectList.empty()) return;

    OBJECT_LIST::iterator it = m_ObjectList.begin();

    while (it != m_ObjectList.end())
    {
        IObject* object = (IObject*)(*it);

        object->Update();

        if (!object->GetActive())
        {
            object->Finalize();

            delete object;

            it = m_ObjectList.erase(it);

            continue;
        }

        ++it;
    }
}

/*
 *  �R���X�g���N�^
 */
CObjectManager::
CObjectManager(void)
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
CObjectManager::
CObjectManager(const CObjectManager& rhs)
{
    (void)rhs;
}

/*
 *  �f�X�g���N�^
 */
CObjectManager::
~CObjectManager(void)
{
}

/*
 *  ������Z�q
 */
CObjectManager&
CObjectManager::
operator=(const CObjectManager& rhs)
{
    (void)rhs;

    return *this;
}