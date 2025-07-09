#pragma once

#include <list>
#include "bullet\bullet_id.h"
#include "bullet\bullet.h"
#include "../launcher/launcher.h"
#include <memory>
class CBulletManager
{
public:
    /*!
     *  @brief      インスタンスの取得
     *
     *  @return     インスタンス
     */
    static CBulletManager& GetInstance(void);

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
     *  @brief      弾リスト型
     */
    using BULLET_LIST = std::list<std::shared_ptr<IBullet>>;


    /*!
     *  @brief      描画
     */
    BULLET_LIST       GetBulletList();
    /*!
     *  @brief      弾生成
     *
     *  @param[in]  category  所属識別子
     *  @param[in]  id          弾ID
     *  @param[in]  pos         位置
     *  @param[in]  dir         向き
     */
    std::shared_ptr<IBullet>        Create(FACTION_CATEGORY category,CShot::BulletParameters* bulletParameters, const CVector3& pos, const CVector3& dir);

    /*!
     *  @brief      弾生成
     *
     *  @param[in]  category  所属識別子
     *  @param[in]  id          弾ID
     *  @param[in]  pos         位置
     *  @param[in]  dir         向き
     */
    std::shared_ptr<IBullet>        Create(FACTION_CATEGORY category, BULLET_ID id, const CVector3& pos, const CVector3& dir);
    
    /*!
     *  @brief      モデルとの反射判定
     */
    void        CheckReflectModel(int model_handle);

private:
    /*!
     *  @brief      コンストラクタ
     */
    CBulletManager(void);

    /*!
     *  @brief      コピーコンストラクタ
     *
     *  @param[in]  rhs     オブジェクト
     */
    CBulletManager(const CBulletManager& rhs);

    /*!
     *  @brief      デストラクタ
     */
    ~CBulletManager(void);

    /*!
     *  @brief      代入演算子
     *
     *  @param[in]  rhs 代入オブジェクト
     *
     *  @return     自身のオブジェクト
     */
    CBulletManager& operator=(const CBulletManager& rhs);


    BULLET_LIST     m_BulletList;   //!< 弾リスト
};
