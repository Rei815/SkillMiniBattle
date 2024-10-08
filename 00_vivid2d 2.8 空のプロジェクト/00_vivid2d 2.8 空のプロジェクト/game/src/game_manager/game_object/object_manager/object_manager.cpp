#include "object_manager.h"
#include "..\..\..\utility\utility.h"
#include "object/fall_object/fall_object.h"
#include "..\gimmick_manager\gimmick_manager.h"
const std::string CObjectManager::m_file_name_list[] = { "data\\Models\\cube.mv1", "data\\Models\\cube.mv1" };

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

    // ���j�b�g�X�V
    UpdateObject();
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
Create(OBJECT_ID id, const CVector3& pos)
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
    }

    if (!object) return nullptr;

    object->Initialize(id, pos);
    m_ObjectList.push_back(object);

    return object;
}

void CObjectManager::SetGimmick(GIMMICK_ID gimmick_id, OBJECT_ID object_id)
{
    if (m_ObjectList.empty()) return;

    OBJECT_LIST::iterator it = m_ObjectList.begin();

    while (it != m_ObjectList.end())
    {
        if ((*it)->GetObjectID() == object_id)
        {
            CGimmickManager::GetInstance().Create(gimmick_id, (*it));
        }

        ++it;
    }

}

CObjectManager::OBJECT_LIST CObjectManager::GetList()
{
    return m_ObjectList;
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