#include "object_manager.h"
#include "../../core/game_object/game_object.h"
#include "../../components/transform_component/transform_component.h"
#include "../../components/model_component/model_component.h"
#include "../../components/collider_component/mesh_collider_component/mesh_collider_component.h"
#include "../../../game/components/player_component/player_component.h"
#include "../../../game/components/gimmick_component/dodge_ball_gimmick_component/dodge_ball_gimmick_component.h"
#include "../../../game/components/gimmick_component/fall_gimmick_component/fall_gimmick_component.h"
#include "../../../game/components/gimmick_component/daruma_fall_down_gimmick_component/daruma_fall_down_gimmick_component.h"
#include "../bullet_manager/bullet/bullet.h"

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
    m_GameObjects.clear();
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
}

/*
 *  描画
 */
void
CObjectManager::
Draw(void)
{
    if (m_GameObjects.empty()) return;

    OBJECT_LIST::iterator it = m_GameObjects.begin();

    while (it != m_GameObjects.end())
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
    m_GameObjects.clear();
}

/*
 *  オブジェクト生成
 */
std::shared_ptr<CGameObject> CObjectManager::Create(OBJECT_ID id, const CTransform& transform, PLAYER_ID player_id)
{
    // CGameObjectのインスタンスを生成
    auto gameObject = std::make_shared<CGameObject>();
    gameObject->SetID(id);
    gameObject->SetTag(GAME_OBJECT_TAG::UNTAGGED);
    // 共通のTransformComponentを設定
    auto transformComp = gameObject->GetComponent<TransformComponent>();
    transformComp->SetTransform(transform);

    switch (id)
    {

    case OBJECT_ID::FALL_FLOOR_MOON:
    case OBJECT_ID::FALL_FLOOR_SUN:
    case OBJECT_ID::FALL_FLOOR_CIRCLE:
    case OBJECT_ID::FALL_FLOOR_SQUARE:
    case OBJECT_ID::FALL_FLOOR_TRIANGLE:
    case OBJECT_ID::FALL_FLOOR_CROSS:
        gameObject->AddComponent<ModelComponent>(MODEL_ID::FALLOUT_FLOOR, true);
        gameObject->AddComponent<FallGimmickComponent>(id);
        gameObject->AddComponent<MeshColliderComponent>();
        gameObject->SetTag(GAME_OBJECT_TAG::FLOOR);
        break;
    case OBJECT_ID::CANNON:
        gameObject->AddComponent<ModelComponent>(MODEL_ID::CANNON);
        //大砲ギミックのセット
        gameObject->AddComponent<DodgeBallGimmickComponent>();
        gameObject->AddComponent<MeshColliderComponent>();
    break;
    
    case OBJECT_ID::OGRE:
        gameObject->AddComponent<ModelComponent>(MODEL_ID::OGRE);
        gameObject->AddComponent<MeshColliderComponent>();
        break;
    case OBJECT_ID::DODGEBALL_STAGE:
        gameObject->AddComponent<ModelComponent>(MODEL_ID::DODGEBALL_STAGE);
        gameObject->AddComponent<MeshColliderComponent>();
        gameObject->SetTag(GAME_OBJECT_TAG::FLOOR);

        break;
    case OBJECT_ID::DARUMA_FALLDOWN_STAGE:
        gameObject->AddComponent<ModelComponent>(MODEL_ID::DARUMA_STAGE);
        gameObject->AddComponent<MeshColliderComponent>();
        gameObject->SetTag(GAME_OBJECT_TAG::FLOOR);
        break;
    case OBJECT_ID::BELT_CONVEYOR:
        gameObject->AddComponent<ModelComponent>(MODEL_ID::BELT_CONVEYOR_STAGE);
        gameObject->AddComponent<MeshColliderComponent>();
        gameObject->SetTag(GAME_OBJECT_TAG::FLOOR);

        break;
    case OBJECT_ID::BELT_CONVEYOR_OBSTRUCTION_1:gameObject->AddComponent<ModelComponent>(MODEL_ID::BELT_CONVEYOR_OBSTRUCTION_1);
    case OBJECT_ID::BELT_CONVEYOR_OBSTRUCTION_2:gameObject->AddComponent<ModelComponent>(MODEL_ID::BELT_CONVEYOR_OBSTRUCTION_2);
    case OBJECT_ID::BELT_CONVEYOR_OBSTRUCTION_3:gameObject->AddComponent<ModelComponent>(MODEL_ID::BELT_CONVEYOR_OBSTRUCTION_3);
    case OBJECT_ID::BELT_CONVEYOR_OBSTRUCTION_4:gameObject->AddComponent<ModelComponent>(MODEL_ID::BELT_CONVEYOR_OBSTRUCTION_4);
    case OBJECT_ID::BELT_CONVEYOR_OBSTRUCTION_5:gameObject->AddComponent<ModelComponent>(MODEL_ID::BELT_CONVEYOR_OBSTRUCTION_5);
    case OBJECT_ID::BELT_CONVEYOR_OBSTRUCTION_6:gameObject->AddComponent<ModelComponent>(MODEL_ID::BELT_CONVEYOR_OBSTRUCTION_6);
        gameObject->AddComponent<MeshColliderComponent>();
        gameObject->SetTag(GAME_OBJECT_TAG::FLOOR);
        break;
    case OBJECT_ID::SKILL_WALL:
        gameObject->AddComponent<ModelComponent>(MODEL_ID::SKILL_WALL);
        gameObject->AddComponent<MeshColliderComponent>();
        gameObject->SetTag(GAME_OBJECT_TAG::WALL);

        break;
    case OBJECT_ID::SKILL_MIMICRY_OBJECT:
        gameObject->AddComponent<ModelComponent>(MODEL_ID::SKILL_MIMICRY_OBJ);
        break;
    case OBJECT_ID::SKILL_BARRIER_OBJECT:
        gameObject->AddComponent<ModelComponent>(MODEL_ID::SKILL_BARRIER_COLLIDER);
        gameObject->AddComponent<MeshColliderComponent>();
        break;
    case OBJECT_ID::PLAYER:
    {
        gameObject->AddComponent<ModelComponent>(MODEL_ID::PLAYER, true);
        gameObject->AddComponent<MeshColliderComponent>();
        gameObject->AddComponent<PlayerComponent>(player_id,transform);
        break;
    }
    }

    if (!gameObject) return nullptr;

    gameObject->Initialize();

    m_GameObjects.emplace_back(gameObject);

    return gameObject;
}

void CObjectManager::DeletePlayer(PLAYER_ID player_id)
{
	// 指定されたプレイヤーIDを持つオブジェクトを検索
	for (auto it = m_GameObjects.begin(); it != m_GameObjects.end();)
	{
		auto& object = *it;
		auto playerComp = object->GetComponent<PlayerComponent>();

		if (playerComp && playerComp->GetPlayerID() == player_id)
		{
			// オブジェクトを削除
			it = m_GameObjects.erase(it);
		}
		else
		{
			++it;
		}
	}
}

CObjectManager::OBJECT_LIST CObjectManager::GetList()
{
    return m_GameObjects;
}

std::shared_ptr<CGameObject> CObjectManager::CheckHitLineForAll(
    const CVector3& start, const CVector3& end, CGameObject* ignore_object, CollisionResult& out_result)
{
    // 管理している全てのゲームオブジェクトをループ
    for (auto& object : m_GameObjects)
    {
        // 自分自身との判定は無視する
        if (object.get() == ignore_object)
        {
            continue;
        }

        // オブジェクトからColliderComponentを取得
        auto collider = object->GetComponent<MeshColliderComponent>();

        // コライダーがあり、かつ有効な場合のみチェック
        if (collider && collider->IsEnabled())
        {
            // コライダーのライン判定を実行
            if (collider->CheckHitLine(start, end, out_result))
            {
                // 最初にヒットしたオブジェクトを返す
                return object;
            }
        }
    }

    // 何にもヒットしなかった
    return nullptr;
}

/*
 *  オブジェクトと弾のアタリ判定
 */
void
CObjectManager::
CheckHitBullet(std::shared_ptr<IBullet> bullet)
{
    // 2. 全オブジェクトのペアを総当たりでチェック
    for (auto& object : m_GameObjects)
    {
        // Aが弾でなければ、当たり判定の主体にならないのでスキップ
        if (!object->IsActive() || bullet->GetBulletCategory() == object->GetCategory())
        {
            continue;
        }

        // --- 「弾」と「プレイヤー」の当たり判定の例 ---
        if (object->GetID() == OBJECT_ID::PLAYER)
        {

            // B(プレイヤー)のColliderを取得
            auto targetCollider = object->GetComponent<MeshColliderComponent>();
            auto targetTransform = object->GetComponent<TransformComponent>();
            auto target = object->GetComponent<PlayerComponent>();
            auto bulletCollider = bullet->GetComponent<MeshColliderComponent>();

            if (targetCollider && targetCollider->IsEnabled())
            {
                bool isHit = false;

                CollisionResult result;
                // 弾の形状に応じて、ターゲットのコライダーに問い合わせる
                switch (bullet->GetColliderID())
                {
                case COLLIDER_ID::SPHERE:
                    isHit = targetCollider->CheckHitSphere(bullet->GetPosition(), bullet->GetRadius(), result); break;

                case COLLIDER_ID::MODEL:
                    isHit = bulletCollider->CheckHitSphere(targetTransform->GetPosition(), target->GetRadius(), result); break;
                    break;
                }

                if (isHit)
                {
                    switch (bullet->GetColliderID())
                    {
                    case COLLIDER_ID::SPHERE:  target->HitBullet(bullet, result.hitPosition);                      break;
                    case COLLIDER_ID::MODEL:
                        CVector3 direction = bullet->GetVelocity().Normalize();
                        if (bullet->GetID() == BULLET_ID::SHOCK_WAVE)
                        {
                            direction = result.hitNormal;
                        }
                        target->Impact(result.hitPosition, direction, bullet->GetPower()); 
                        
                        break;

                    }
                    // A(弾)を消滅させる
                    bullet->Delete();
                }
            }
        }
    }
}
///*
//* 当たったオブジェクトを返す
//*/
//std::shared_ptr<IObject> CObjectManager::CheckHitObject(std::shared_ptr<CPlayer> player)
//{
//    if (m_ObjectList.empty()) return nullptr;
//    OBJECT_LIST::iterator it = m_ObjectList.begin();
//
//    while (it != m_ObjectList.end())
//    {
//        std::shared_ptr<IObject> object = *it;
//        if (object->GetModelHandle().GetHandle() == VIVID_DX_ERROR || object->GetColliderActiveFlag() == false)
//        {
//            ++it;
//            continue;
//        }
//
//        //垂直方向の判定-----------------------------------------------------
//
//        float radius = player->GetRadius();
//        float offset = radius / 2.0f;
//        for (int i = 0; i < 9; ++i)
//        {
//            CVector3 unit_pos = player->GetPosition();
//
//            CVector3 start = unit_pos + CVector3(-offset + (offset) * (i % 3), 0.0, -offset + (offset) * (i / 3));
//            CVector3 end_position = start + CVector3(0, -radius, 0);
//
//            if (object->GetModelHandle().CheckHitLine(start, end_position) == true)
//                return object;
//        }
//
//        ++it;
//    }
//    return nullptr;
//}
//
/*
 *  オブジェクト更新
 */
void
CObjectManager::
UpdateObject(void)
{
    if (m_GameObjects.empty()) return;

    OBJECT_LIST::iterator it = m_GameObjects.begin();

    while (it != m_GameObjects.end())
    {
        std::shared_ptr<CGameObject> gameObject = *it;

        gameObject->Update(vivid::GetDeltaTime());

        if (!gameObject->IsActive())
        {
            gameObject->Finalize();

            it = m_GameObjects.erase(it);

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