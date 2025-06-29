#pragma once

#include "vivid.h"
#include "model_id.h" // MODEL_ID を使うため
#include <string>    // std::stringのため

class CVector3; // 前方宣言

class CModel
{
private:
    int m_Handle;

public:
    // コンストラクタで、MODEL_IDまたはファイルパスを受け取り、モデルをロードします
    CModel(MODEL_ID id);

    // デストラクタで、モデルを自動的にアンロードします
    ~CModel();

    // モデルハンドルを取得するための、唯一の公開メソッド
    int GetHandle() const;

    // --- モデルデータ自体に対する操作は、ここに残します ---
    bool CheckHitLine(const CVector3& startPos, const CVector3& endPos) const;
    CVector3 GetHitLinePosition(const CVector3& startPos, const CVector3& endPos) const;
    unsigned int GetMaterialDif(int material_index);
    void SetMaterialDif(int material_index, unsigned int color);

private:
    // 内部でのみ使われるロード/アンロード処理
    void Load(const std::string& file_name);
    void Unload(void);
};