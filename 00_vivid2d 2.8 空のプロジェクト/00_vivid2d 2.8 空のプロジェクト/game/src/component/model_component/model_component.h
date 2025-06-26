#pragma once
#include "../component.h"
#include "../../game_manager/game_object/model/model_id.h" // MODEL_ID を使うため
#include <memory>

// 前方宣言
class CGameObject;
class CModel;
class TransformComponent;

class ModelComponent : public IComponent
{
private:
    std::shared_ptr<CModel> m_model; // 描画するモデルデータ
    CGameObject* m_owner = nullptr;  // オーナーオブジェクトへのポインタ

public:
    // ★変更点：コンストラクタで、ファイルパスではなく MODEL_ID を受け取る
    ModelComponent(MODEL_ID id);
    ~ModelComponent() override = default;

    void Update(float delta_time, CGameObject* owner) override {}

    // OnAttachメソッドの宣言を追加
    void OnAttach(CGameObject* owner) override;

    // 独自のDrawメソッド
    void Draw();
};