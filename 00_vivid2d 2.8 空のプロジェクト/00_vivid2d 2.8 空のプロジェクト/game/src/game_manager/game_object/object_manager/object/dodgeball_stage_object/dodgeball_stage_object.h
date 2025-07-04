#pragma once
#include "../../../model/model.h"
#include "..\object.h"
#include "..\..\..\..\..\utility\utility.h"

class CDogeballStageObject : public IObject
{
public:
    CDogeballStageObject();
    ~CDogeballStageObject();

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

private:

    static const std::string m_model_file_name;


};