#pragma once
#include <string>
#include <map>
#include "../model/model_id.h"

class CModelManager
{

public:
    /*!
     *  @brief      インスタンスの取得
     *
     *  @return     インスタンス
     */
    static CModelManager& GetInstance(void);

    // ... GetInstance()など、以前の提案と同じ ...
    const std::string& GetModelFilePath(MODEL_ID id) const;
private:
    /*!
     *  @brief      コンストラクタ
     */
    CModelManager(void);

    /*!
     *  @brief      コピーコンストラクタ
     *
     *  @param[in]  rhs     オブジェクト
     */
    CModelManager(const CModelManager& rhs);

    /*!
     *  @brief      デストラクタ
     */
    ~CModelManager(void);

    /*!
     *  @brief      代入演算子
     *
     *  @param[in]  rhs 代入オブジェクト
     *
     *  @return     自身のオブジェクト
     */
    CModelManager& operator=(const CModelManager& rhs);

    std::map<MODEL_ID, std::string> m_ModelPaths;
    std::map<std::string, MODEL_ID> m_StringToIdMap;
};