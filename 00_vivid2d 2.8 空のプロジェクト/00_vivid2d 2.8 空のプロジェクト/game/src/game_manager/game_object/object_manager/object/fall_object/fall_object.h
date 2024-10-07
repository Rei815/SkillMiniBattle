#pragma once
#include "../../../model_manager/model/model.h"
#include "mark_id.h"
#include "..\object.h"

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
    void    Initialize(const CVector3& position);

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

    /*!
     *  @brief      状態設定
     *
     *  @param[in]  state  フォールオブジェクトの状態
     */
    void            SetState(FALL_OBJECT_STATE active);

private:
    static const float  m_fall_speed;
    float               m_FallSpeed;
    FALL_OBJECT_STATE   m_FallObjectState;
    MARK_ID             m_MarkID;
};