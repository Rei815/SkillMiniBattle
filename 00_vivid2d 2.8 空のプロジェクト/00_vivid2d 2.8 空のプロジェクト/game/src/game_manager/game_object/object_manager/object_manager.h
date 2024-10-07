#pragma once

#include "vivid.h"
#include <list>
#include "object/object.h"
#include "object/object_id.h"
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
     */
    void        Create(OBJECT_ID id, const CVector3& pos);

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

    /*!
     *  @brief      オブジェクトリスト型
     */
    using OBJECT_LIST = std::list<IObject*>;

    OBJECT_LIST             m_ObjectList;             //!< オブジェクトリスト
};