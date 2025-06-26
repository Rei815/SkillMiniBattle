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
    std::shared_ptr<CModel> m_model; // �`�悷�郂�f���f�[�^
    CGameObject* m_owner = nullptr;  // �I�[�i�[�I�u�W�F�N�g�ւ̃|�C���^

public:
    // ���ύX�_�F�R���X�g���N�^�ŁA�t�@�C���p�X�ł͂Ȃ� MODEL_ID ���󂯎��
    ModelComponent(MODEL_ID id);
    ~ModelComponent() override = default;

    void Update(float delta_time, CGameObject* owner) override {}

    // OnAttach���\�b�h�̐錾��ǉ�
    void OnAttach(CGameObject* owner) override;

    // �Ǝ���Draw���\�b�h
    void Draw();
};