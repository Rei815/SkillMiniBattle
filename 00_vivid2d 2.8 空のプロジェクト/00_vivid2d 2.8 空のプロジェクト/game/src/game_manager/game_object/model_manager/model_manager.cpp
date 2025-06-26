#include "model_manager.h"
// ★★★ 既存のCSVローダーをインクルード ★★★
#include "../../../utility/csv_loader/csv_loader.h" // あなたのプロジェクトのパスに合わせてください

CModelManager::CModelManager()
{
    // --- 準備1：文字列とenumの対応表を作る ---
    m_stringToIdMap["PLAYER"] = MODEL_ID::PLAYER;
    // ...

    // --- 準備2：CSVローダーのインスタンスを作成 ---
    CCSVLoader csvLoader;
    csvLoader.Load("data/model_data.csv"); // model_data.csvを読み込ませる

    // --- 本処理：CSVの行をループで回して、データを登録していく ---
    // GetRows()でCSVの行数を取得し、ループを回す
    // ※ヘッダー行があるので、i=1から始めるのが良いでしょう
    for (int i = 1; i < csvLoader.GetRows(); ++i)
    {
        // 1列目(cols=0)から、ID文字列（"PLAYER"など）を取得
        std::string id_str = csvLoader.GetString(i, 0);

        // 2列目(cols=1)から、ファイルパス文字列を取得
        std::string filepath = csvLoader.GetString(i, 1);

        // 文字列IDをenumのIDに変換
        if (m_stringToIdMap.count(id_str))
        {
            MODEL_ID id = m_stringToIdMap.at(id_str);
            // 最終的なデータマップに登録
            m_modelPaths[id] = filepath;
        }
    }
}

// GetModelFilePathメソッドは以前の提案のままでOK
const std::string& CModelManager::GetModelFilePath(MODEL_ID id) const
{
    return m_modelPaths.at(id);
}