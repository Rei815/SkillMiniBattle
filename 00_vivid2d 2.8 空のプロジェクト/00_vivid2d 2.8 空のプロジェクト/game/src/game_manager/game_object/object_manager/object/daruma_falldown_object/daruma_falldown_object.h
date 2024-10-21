#pragma once
#include "../../../model_manager/model/model.h"
#include "..\object.h"
#include "..\..\..\..\..\utility\utility.h"
enum class DARUMA_FALLDOWN_OBJECT_STATE
{
    WAIT,
    FALL,
};
class CDaruma_FallDownObject : public IObject
{
public:
    CDaruma_FallDownObject();
    ~CDaruma_FallDownObject();

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

private:
    static const float                     m_start_height;
    static const float                     m_remove_height;
    static const float                     m_invisible_alpha;
    static const std::string               m_file_name_list[];
    float                                  m_FallSpeed;
    DARUMA_FALLDOWN_OBJECT_STATE           m_Daruma_FallDownObjectState;
    CTimer                                 m_Timer;
};