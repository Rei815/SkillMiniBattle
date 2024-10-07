
#pragma once
#include "..\gimmick.h"
#include "fall_object/fall_object.h"
#include <list>
class CFallGimmick : public CGimmick
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     */
    CFallGimmick();

    /*!
     *  @brief      デストラクタ
     */
    ~CFallGimmick(void);

    /*!
     *  @brief      初期化
     *
     */
    void    Initialize();

    /*!
     *  @brief      更新
     */
    void    Update(void);

    /*!
     *  @brief      描画
     */
    void    Draw(void);

    /*!
     *  @brief      解放
     */
    void    Finalize(void);

    /*!
     *  @brief      オブジェクト生成
     *
     *  @param[in]  id              オブジェクトのID
     */
    void        Create(MARK_ID id, const CVector3& position);

    void        Fall(MARK_ID id);
private:
    /*!
     *  @brief      フォールオブジェクトリスト型
     */
    using FALL_OBJECT_LIST = std::list<CFallObject*>;

    FALL_OBJECT_LIST             m_FallObjectList;             //!< フォールオブジェクトリスト

};
