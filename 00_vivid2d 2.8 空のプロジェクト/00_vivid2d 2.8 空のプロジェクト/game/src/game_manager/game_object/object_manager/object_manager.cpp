#include "object_manager.h"
#include "..\..\..\utility\utility.h"
#include "object/fall_object/fall_object.h"
#include "object/cannon_object/cannon_object.h"
#include "object/ogre_object/ogre_object.h"
#include "object/dodgeball_stage_object/dodgeball_stage_object.h"
#include "..\gimmick_manager\gimmick_manager.h"
#include "..\unit_manager\unit_manager.h"

/*
 *  インスタンスの取得
 */
CObjectManager&
CObjectManager::
GetInstance(void)
{
    static CObjectManager instance;

    return instance;
}

/*
 *  初期化
 */
void
CObjectManager::
Initialize(void)
{
    m_ObjectList.clear();
}

/*
 *  更新
 */
void
CObjectManager::
Update(void)
{

    // オブジェクト更新
    UpdateObject();

    OBJECT_LIST::iterator it = m_ObjectList.begin();

    while (it != m_ObjectList.end())
    {
        CUnitManager::GetInstance().CheckHitObject((*it));
        ++it;
    }
}

/*
 *  描画
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
 *  解放
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
 *  オブジェクト生成
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
    if (m_ObjectList.empty()) return nullptr;
    OBJECT_LIST::iterator it = m_ObjectList.begin();

    while (it != m_ObjectList.end())
    {

        if ((*it)->GetModel().GetModelHandle() == VIVID_DX_ERROR)
            return nullptr;

        //垂直方向の判定-----------------------------------------------------

        CVector3 startPos[4];

        for (int i = 0; i < 4; i++)
        {
            startPos[i] = player->GetPosition();
        }

        //左奥にする
        startPos[0].x -= player->GetRadius();
        startPos[0].z += player->GetRadius();

        //右奥にする
        startPos[1].x += player->GetRadius();
        startPos[1].z += player->GetRadius();

        //左前にする
        startPos[2].x -= player->GetRadius();
        startPos[2].z -= player->GetRadius();

        //右前にする
        startPos[3].x += player->GetRadius();
        startPos[3].z -= player->GetRadius();

        CVector3 endPos[4];

        for (int i = 0; i < 4; i++)
        {
            endPos[i] = player->GetPosition();
            endPos[i].y -= player->GetHeight() / 2.0f;

        }

        for (int i = 0; i < 4; i++)
            if ((*it)->GetModel().CheckHitLine(startPos[i], endPos[i]) == true)
                return (*it);

        ++it;
    }
    return nullptr;
}

/*
 *  オブジェクト更新
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
 *  コンストラクタ
 */
CObjectManager::
CObjectManager(void)
{
}

/*
 *  コピーコンストラクタ
 */
CObjectManager::
CObjectManager(const CObjectManager& rhs)
{
    (void)rhs;
}

/*
 *  デストラクタ
 */
CObjectManager::
~CObjectManager(void)
{
}

/*
 *  代入演算子
 */
CObjectManager&
CObjectManager::
operator=(const CObjectManager& rhs)
{
    (void)rhs;

    return *this;
}