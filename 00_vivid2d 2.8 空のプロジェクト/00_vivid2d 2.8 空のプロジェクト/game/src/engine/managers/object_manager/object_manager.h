#pragma once

#include "vivid.h"
#include <list>
#include "object_id.h"
#include <memory>
#include "../../../engine/core/game_object/game_object.h"
#include "../bullet_manager/bullet/bullet.h"

class CObjectManager
{
public:
    /*!
     *  @brief      インスタンスの取得
     *
     *  @return     インスタンス
     */
    static CObjectManager& GetInstance(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(void);

    /*!
     *  @brief      更新
     */
    void        Update(void);

    /*!
     *  @brief      描画
     */
    void        Draw(void);

    /*!
     *  @brief      解放
     */
    void        Finalize(void);

    /*!
     *  @brief      オブジェクト生成
     *
     *  @param[in]  id              オブジェクトID
     *  @param[in]  position        位置
     */
    std::shared_ptr<CGameObject>    Create(OBJECT_ID id, const CTransform& transform, PLAYER_ID player_id = PLAYER_ID::NONE);

	/*!
	 *  @brief      プレイヤーを削除
	 *
	 *  @param[in]  player_id   プレイヤーID
	 *
	 */
    void DeletePlayer(PLAYER_ID player_id);

    /*!
     *  @brief      オブジェクトリスト型
     */
    using OBJECT_LIST = std::list<std::shared_ptr<CGameObject>>;

    /*!
     *  @brief      リスト取得
     *
     *  @return     オブジェクトリスト
     */
    OBJECT_LIST GetList();

    template<typename T>
    std::vector<std::shared_ptr<CGameObject>> GetObjectsWithComponent()
    {
        std::vector<std::shared_ptr<CGameObject>> result;
        for (auto& obj : m_GameObjects)
        {
            if (obj->HasComponent<T>())
            {
                result.push_back(obj);
            }
        }
        return result;
    }

    // 詳細バージョン（衝突位置も取得する）
    std::shared_ptr<CGameObject> CheckHitLineForAll(
        const CVector3& start,
        const CVector3& end,
        CGameObject* ignore_object, // 自分自身を無視するための引数
        CVector3& out_hitPosition   // 衝突位置を格納する
    );

    // シンプルバージョン（当たり判定の有無だけ）
    std::shared_ptr<CGameObject> CheckHitLineForAll(
        const CVector3& start,
        const CVector3& end,
        CGameObject* ignore_object
    );

    /*!
     *  @brief      ユニットと弾とのアタリ判定
     *
     *  @param[in]  bullet  弾クラス
     */
    void        CheckHitBullet(std::shared_ptr<IBullet> bullet);

private:

    /*!
     *  @brief      オブジェクト更新
     */
    void        UpdateObject(void);


    /*!
     *  @brief      コンストラクタ
     */
    CObjectManager(void);

    /*!
     *  @brief      コピーコンストラクタ
     *
     *  @param[in]  rhs     オブジェクト
     */
    CObjectManager(const CObjectManager& rhs);

    /*!
     *  @brief      デストラクタ
     */
    ~CObjectManager(void);

    /*!
     *  @brief      代入演算子
     *
     *  @param[in]  rhs 代入オブジェクト
     *
     *  @return     自身のオブジェクト
     */
    CObjectManager& operator=(const CObjectManager& rhs);

    OBJECT_LIST             m_GameObjects;             //!< オブジェクトリスト
};