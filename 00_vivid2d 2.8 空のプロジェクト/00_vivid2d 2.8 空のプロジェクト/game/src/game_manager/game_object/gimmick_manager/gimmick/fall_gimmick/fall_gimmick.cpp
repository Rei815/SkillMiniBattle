#include "fall_gimmick.h"
CFallGimmick::CFallGimmick()
{
}

CFallGimmick::~CFallGimmick(void)
{
}

void CFallGimmick::Initialize()
{
    m_FallObjectList.clear();
    Create(MARK_ID::CIRCLE, CVector3(0,100,0)); 
}

void CFallGimmick::Update(void)
{
    if (m_FallObjectList.empty()) return;

    FALL_OBJECT_LIST::iterator it = m_FallObjectList.begin();

    while (it != m_FallObjectList.end())
    {
        CFallObject* object = (CFallObject*)(*it);

        object->Update();

        if (!object->GetActive())
        {
            object->Finalize();

            delete object;

            it = m_FallObjectList.erase(it);

            continue;
        }

        ++it;
    }

}

void CFallGimmick::Draw(void)
{
    if (m_FallObjectList.empty()) return;

    FALL_OBJECT_LIST::iterator it = m_FallObjectList.begin();

    while (it != m_FallObjectList.end())
    {
        (*it)->Draw();

        ++it;
    }

}

void CFallGimmick::Finalize(void)
{
    if (m_FallObjectList.empty()) return;

    FALL_OBJECT_LIST::iterator it = m_FallObjectList.begin();

    while (it != m_FallObjectList.end())
    {
        (*it)->Finalize();

        delete (*it);

        ++it;
    }

    m_FallObjectList.clear();

}

void CFallGimmick::Create(MARK_ID id, const CVector3& position)
{
    CFallObject* object = nullptr;

    object = new CFallObject();
    if (!object) return;
    switch (id)
    {
    case MARK_ID::CIRCLE:    object->Initialize(MARK_ID::CIRCLE, position);     break;
    case MARK_ID::STAR:    object->Initialize(MARK_ID::STAR, position);     break;
        break;
    }

    
    m_FallObjectList.push_back(object);

}

void CFallGimmick::Fall(MARK_ID id)
{
    if (m_FallObjectList.empty()) return;

    FALL_OBJECT_LIST::iterator it = m_FallObjectList.begin();

    while (it != m_FallObjectList.end())
    {
        CFallObject* object = (CFallObject*)(*it);

        if (object->GetID() == id)
            object->SetState(FALL_OBJECT_STATE::FALL);
    }
}
