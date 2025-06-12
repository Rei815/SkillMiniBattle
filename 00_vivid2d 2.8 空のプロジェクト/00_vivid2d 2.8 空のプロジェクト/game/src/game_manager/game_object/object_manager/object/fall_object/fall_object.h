#pragma once
#include "../../../model/model.h"
#include "mark_id.h"
#include "..\object.h"
#include "..\..\..\..\..\utility\utility.h"
enum class FALL_OBJECT_STATE
{
    WAIT,
    FALL,
};
class CFallObject : public IObject
{
public:
    CFallObject();
    ~CFallObject();

    /*!
     *  @brief      初期化
     *
     */
    void    Initialize(OBJECT_ID id, const CTransform& transform);

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
     *  @brief      ID取得
     *
     *  @return     マークID
     */
    MARK_ID         GetID(void);

private:
    enum class STATE
    {
        WAIT,
        ACTIVE,
    };
    static const std::string    m_file_name_list[];
    MARK_ID                     m_MarkID;
};