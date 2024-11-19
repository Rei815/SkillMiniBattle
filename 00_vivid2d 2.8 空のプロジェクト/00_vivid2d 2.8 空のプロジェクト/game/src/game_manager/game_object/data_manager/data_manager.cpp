#include "data_manager.h"
/*
 *  インスタンスの取得
 */
CDataManager&
CDataManager::
GetInstance(void)
{
    static CDataManager instance;

    return instance;
}

/*
 *  初期化
 */
void
CDataManager::
Initialize(void)
{
}

/*
 *  更新
 */
void
CDataManager::Update(void)
{
}

/*
 *  解放
 */
void CDataManager::Finalize(void)
{
}

/*
 *  コンストラクタ
 */
CDataManager::
CDataManager(void)
{
}

/*
 *  コピーコンストラクタ
 */
CDataManager::
CDataManager(const CDataManager& rhs)
{
    (void)rhs;
}

/*
 *  デストラクタ
 */
CDataManager::
~CDataManager(void)
{
}

/*
 *  代入演算子
 */
CDataManager&
CDataManager::
operator=(const CDataManager& rhs)
{
    (void)rhs;

    return *this;
}
