#include "object_manager.h"
#include "..\..\..\utility\utility.h"
#include "object/fall_object/fall_object.h"
#include "object/cannon_object/cannon_object.h"
#include "object/ogre_object/ogre_object.h"
#include "object/dodgeball_stage_object/dodgeball_stage_object.h"
#include "object/daruma_falldown_stage_object/daruma_falldown_stage_object.h"
#include "object/skill_wall_object/skill_wall_object.h"
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
    case OBJECT_ID::DARUMA_FALLDOWN_STAGE_OBJECT:
        object = new CDarumaFallDownStageObject(); break;
    case OBJECT_ID::SKILL_WALL_OBJECT:
        object = new CSkillWallObject(); break;
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
* 当たったオブジェクトを返す
*/
IObject* CObjectManager::CheckHitObject(CPlayer* player)
{
    if (m_ObjectList.empty()) return nullptr;
    OBJECT_LIST::iterator it = m_ObjectList.begin();

    while (it != m_ObjectList.end())
    {

        if ((*it)->GetModel().GetModelHandle() == VIVID_DX_ERROR || (*it)->GetColliderActiveFlag() == false)
            return nullptr;

        //垂直方向の判定-----------------------------------------------------

        float radius = player->GetRadius();
        const int check_point_count = 4;
        for (int i = 0; i < 9; ++i)
        {
            CVector3 unit_pos = player->GetPosition();

            CVector3 start = unit_pos + CVector3(-radius + (radius) * (i % 3), 0.0, -radius + (radius) * (i / 3));
            CVector3 end_position = start + CVector3(0, - radius * 2, 0);

            if ((*it)->GetModel().CheckHitLine(start, end_position) == true)
                return (*it);
        }

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