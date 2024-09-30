#pragma once

#include "vivid.h"
#include "..\..\..\utility\utility.h"
#include <list>
#include "model/model.h"

class CModelManager
{
public:
    /*!
     *  @brief      インスタンスの取得
     *
     *  @return     インスタンス
     */
    static CModelManager& GetInstance(void);

    /*!
     *  @brief      読み込み
     */
    void        Load(void);

    /*!
     *  @brief      削除
     */
    void        UnLoad(void);

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

    /*!
     *  @brief      モデルリスト型
     */
    using MODEL_LIST = std::list<CModel*>;

    MODEL_LIST              m_ModelList;                                //!< モデルリスト

    static const char*      m_model_file_names[(int)MODEL_ID::MAX];     //!< モデルのファイル名

    int      m_model_handles[(int)MODEL_ID::MAX];     //!< モデルのファイル名

    int                     m_Handle;                                   //!< ハンドル
};
