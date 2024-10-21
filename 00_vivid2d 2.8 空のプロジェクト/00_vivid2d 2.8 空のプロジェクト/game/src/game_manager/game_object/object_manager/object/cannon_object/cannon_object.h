#pragma once
#include "../../../model_manager/model/model.h"
#include "..\object.h"
#include "..\..\..\..\..\utility\utility.h"

class CCannonObject : public IObject
{
public:
    CCannonObject();
    ~CCannonObject();

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

private:

    static const std::string m_model_file_name;

};