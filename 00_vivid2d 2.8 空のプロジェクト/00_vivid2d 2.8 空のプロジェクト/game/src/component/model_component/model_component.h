#pragma once
#include "../component.h"
#include "../../game_manager/game_object/model/model_id.h" // MODEL_ID ���g������
#include <memory>

// �O���錾
class CGameObject;
class CModel;
class TransformComponent;

class ModelComponent : public IComponent
{
private:
    std::shared_ptr<CModel> m_Model; // �`�悷�郂�f���f�[�^
    CGameObject* m_Owner = nullptr;  // �I�[�i�[�I�u�W�F�N�g�ւ̃|�C���^

public:
    ModelComponent(MODEL_ID id);
    ~ModelComponent() override = default;

    void Update(float delta_time, CGameObject* owner) override {}

    void OnAttach(CGameObject* owner) override;

    void Draw();

    int GetModelHandle() const;
};