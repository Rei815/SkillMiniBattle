#include "model_manager.h"
const char* CModelManager::m_model_file_names[] =
{
    "data\\cube.mv1",
    "data\\flat_cube.mv1",
};

/*
 *  インスタンスの取得
 */
CModelManager& CModelManager::GetInstance(void)
{
    static CModelManager instance;

    return instance;
}
/*
 *  読み込み
 */
void
CModelManager::Load(void)
{
    for (int i = 0; i < (int)MODEL_ID::MAX; ++i)
    {
        //// ロード済みの3Dモデルを検索
        //int handle = FindLoadedModel(m_model_file_names[i]);

        //// 3Dモデルが見つかった
        //if (m_model_handles[i] != VIVID_DX_ERROR)
        //	return;

        //3Dモデルの読み込み
        int handle = MV1LoadModel(m_model_file_names[i]);
        using namespace vivid::core;
        VIVID_DX_ASSERT(m_Handle, (TCHAR)m_model_file_names[i] + "の読み込みに失敗しました。");
        m_model_handles[i] = handle;
    }
}
void CModelManager::UnLoad(void)
{
    for (int i = 0; i < (int)MODEL_ID::MAX; ++i)
    {
        //エラー
        if (m_model_handles[i] == VIVID_DX_ERROR)
            return;

        //削除
        MV1DeleteModel(m_model_handles[i]);
    }

}
/*
 *  初期化
 */
void
CModelManager::Initialize(void)
{
    m_ModelList.clear();
}

/*
 *  更新
 */
void
CModelManager::Update(void)
{
}

/*
 *  描画
 */
void
CModelManager::Draw(void)
{
    if (m_ModelList.empty()) return;

    MODEL_LIST::iterator it = m_ModelList.begin();

    while (it != m_ModelList.end())
    {
        (*it)->Draw();

        ++it;
    }
}

/*
 *  解放
 */
void
CModelManager::Finalize(void)
{
    if (m_ModelList.empty()) return;

    MODEL_LIST::iterator it = m_ModelList.begin();

    while (it != m_ModelList.end())
    {
        (*it)->Finalize();

        delete (*it);

        ++it;
    }

    m_ModelList.clear();
}


/*
 *  コンストラクタ
 */
CModelManager::CModelManager(void)
{
}

/*
 *  コピーコンストラクタ
 */
CModelManager::CModelManager(const CModelManager& rhs)
{
    (void)rhs;
}

/*
 *  デストラクタ
 */
CModelManager::
~CModelManager(void)
{
}

/*
 *  代入演算子
 */
CModelManager& CModelManager::operator=(const CModelManager& rhs)
{
    (void)rhs;

    return *this;
}
