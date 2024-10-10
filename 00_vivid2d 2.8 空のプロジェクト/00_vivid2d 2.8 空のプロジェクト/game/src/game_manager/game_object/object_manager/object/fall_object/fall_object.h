#pragma once
#include "../../../model_manager/model/model.h"
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
    void    Initialize(OBJECT_ID id, const CVector3& position);

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
     *  @brief      アクティブフラグ取得
     *
     *  @return     アクティブフラグ
     */
    bool            GetActive(void);

    /*!
     *  @brief      アクティブフラグ設定
     *
     *  @param[in]  active  アクティブフラグ
     */
    void            SetActive(bool active);

    /*!
     *  @brief      ID取得
     *
     *  @return     マークID
     */
    MARK_ID         GetID(void);

private:
    static const float          m_start_height;
    static const float          m_remove_height;
    static const float          m_invisible_alpha;

    float                       m_FallSpeed;
    FALL_OBJECT_STATE           m_FallObjectState;
    MARK_ID                     m_MarkID;
    CTimer                      m_Timer;

};