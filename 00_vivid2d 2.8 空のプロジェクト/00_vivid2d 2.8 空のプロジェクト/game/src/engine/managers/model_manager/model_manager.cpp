#include "model_manager.h"
#include "../../utility/csv_loader/csv_loader.h"

 /*
  *  インスタンスの取得
  */
CModelManager& CModelManager::GetInstance(void)
{
    static CModelManager instance;

    return instance;
}

CModelManager::CModelManager()
{
    // --- 準備1：文字列とenumの対応表を作る ---
    m_StringToIdMap["PLAYER"] = MODEL_ID::PLAYER;
    m_StringToIdMap["BULLET"] = MODEL_ID::BULLET;
    m_StringToIdMap["CANNON"] = MODEL_ID::CANNON;
    m_StringToIdMap["BARRIER"] = MODEL_ID::BARRIER;
    m_StringToIdMap["OGRE"] = MODEL_ID::OGRE;
    m_StringToIdMap["FALLOUT_FLOOR"] = MODEL_ID::FALLOUT_FLOOR;
    m_StringToIdMap["DODGEBALL_STAGE"] = MODEL_ID::DODGEBALL_STAGE;
    m_StringToIdMap["DARUMA_STAGE"] = MODEL_ID::DARUMA_STAGE;
    m_StringToIdMap["BELT_CONVEYOR_STAGE"] = MODEL_ID::BELT_CONVEYOR_STAGE;
    m_StringToIdMap["BELT_CONVEYOR_OBSTRUCTION_1"] = MODEL_ID::BELT_CONVEYOR_OBSTRUCTION_1;
    m_StringToIdMap["BELT_CONVEYOR_OBSTRUCTION_2"] = MODEL_ID::BELT_CONVEYOR_OBSTRUCTION_2;
    m_StringToIdMap["BELT_CONVEYOR_OBSTRUCTION_3"] = MODEL_ID::BELT_CONVEYOR_OBSTRUCTION_3;
    m_StringToIdMap["BELT_CONVEYOR_OBSTRUCTION_4"] = MODEL_ID::BELT_CONVEYOR_OBSTRUCTION_4;
    m_StringToIdMap["BELT_CONVEYOR_OBSTRUCTION_5"] = MODEL_ID::BELT_CONVEYOR_OBSTRUCTION_5;
    m_StringToIdMap["BELT_CONVEYOR_OBSTRUCTION_6"] = MODEL_ID::BELT_CONVEYOR_OBSTRUCTION_6;
    m_StringToIdMap["SKILL_BARRIER_COLLIDER"] = MODEL_ID::SKILL_BARRIER_COLLIDER;
    m_StringToIdMap["SKILL_MIMICRY_OBJ"] = MODEL_ID::SKILL_MIMICRY_OBJ;
    m_StringToIdMap["SKILL_WALL"] = MODEL_ID::SKILL_WALL;
    m_StringToIdMap["STOMP_COLL"] = MODEL_ID::STOMP_COLL;

    // --- 準備2：CSVローダーのインスタンスを作成 ---
     CCSVLoader csvLoader;
    csvLoader.Load("data/model_data.csv"); // model_data.csvを読み込ませる

    for (int i = 0; i < csvLoader.GetRows(); ++i)
    {
        // 1列目(cols=0)から、ID文字列（"PLAYER"など）を取得
        std::string id_str = csvLoader.GetString(i, 0);

        // 2列目(cols=1)から、ファイルパス文字列を取得
        std::string filepath = csvLoader.GetString(i, 1);

        // 文字列IDをenumのIDに変換
        if (m_StringToIdMap.count(id_str))
        {
            MODEL_ID id = m_StringToIdMap.at(id_str);
            // 最終的なデータマップに登録
            m_ModelPaths[id] = filepath;
        }
    }
    // 読み込んだパス情報を元に、全てのモデルをロードする
    LoadAllModels();
}

// GetModelFilePathメソッドは以前の提案のままでOK
const std::string& CModelManager::GetModelFilePath(MODEL_ID id) const
{
    return m_ModelPaths.at(id);
}
void CModelManager::LoadAllModels()
{
    // m_ModelPathsに登録されている全てのモデルをループしてロード
    for (const auto& pair : m_ModelPaths)
    {
        MODEL_ID id = pair.first;
        const std::string& path = pair.second;

        // モデルをロードし、ハンドルを取得
        int handle = MV1LoadModel(path.c_str());

        // 取得したハンドルをm_ModelHandlesマップに保存
        m_ModelHandles[id] = handle;
    }
}

void CModelManager::UnloadAllModels()
{
    // ロードした全てのモデルハンドルをループして解放
    for (const auto& pair : m_ModelHandles)
    {
        MV1DeleteModel(pair.second);
    }
    // マップをクリア
    m_ModelHandles.clear();
}

int CModelManager::GetModelHandle(MODEL_ID id) const
{
    // マップに指定されたIDが存在するかチェック
    if (m_ModelHandles.count(id))
    {
        // 存在すれば、対応するハンドルを返す
        return m_ModelHandles.at(id);
    }

    // 存在しない場合はエラーとして-1を返す
    return VIVID_DX_ERROR;
}
/*
 *  コピーコンストラクタ
 */
CModelManager::
CModelManager(const CModelManager& rhs)
{
    (void)rhs;
}

/*
 *  デストラクタ
 */
CModelManager::
~CModelManager(void)
{
    // アプリケーション終了時に、ロードした全てのモデルを解放する
    UnloadAllModels();
}

/*
 *  代入演算子
 */
CModelManager&
CModelManager::
operator=(const CModelManager& rhs)
{
    (void)rhs;

    return *this;
}
