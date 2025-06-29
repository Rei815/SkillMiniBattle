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
    std::shared_ptr<CModel> m_Model; // 描画するモデルデータ
    CGameObject* m_Owner = nullptr;  // オーナーオブジェクトへのポインタ

public:
    ModelComponent(MODEL_ID id);
    ~ModelComponent() override = default;

    void Update(float delta_time, CGameObject* owner) override {}

    void OnAttach(CGameObject* owner) override;

    void Draw();

    int GetModelHandle() const;
};