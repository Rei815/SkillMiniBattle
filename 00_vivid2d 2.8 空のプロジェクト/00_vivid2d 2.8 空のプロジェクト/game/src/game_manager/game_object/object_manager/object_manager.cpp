#include "object_manager.h"
#include "..\..\..\utility\utility.h"
#include "object/fall_object/fall_object.h"
#include "object/cannon_object/cannon_object.h"
#include "object/dodgeball_stage_object/dodgeball_stage_object.h"
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
    case OBJECT_ID::DODGEBALL_STAGE_OBJECT:
        object = new CDogeballStageObject(); break;
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

IObject* CObjectManager::CheckHitObject(CPlayer* player)
{
    if (m_ObjectList.empty()) return;
    OBJECT_LIST::iterator it = m_ObjectList.begin();

    while (it != m_ObjectList.end())
    {

        if ((*it)->GetModel().GetModelHandle() == VIVID_DX_ERROR)
            return;

        CVector3 startPos = player->GetPosition();

        CVector3 endPos = player->GetPosition();
        endPos.y -= player->GetRadius();

        CVector3 hitPos;

        // �����̕`��
        DrawLine3D(startPos, endPos, GetColor(255, 255, 0));

        if ((*it)->GetModel().CheckHitLine(startPos, endPos) == true)
        {

            hitPos = (*it)->GetModel().GetHitLinePosition(startPos, endPos);

            float diffHeight = endPos.y - hitPos.y;

            CVector3 unitPos = player->GetPosition();
            unitPos.y -= diffHeight;
            player->SetPosition(unitPos);
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