#pragma once

#include "vivid.h"
#include "model_id.h" // MODEL_ID ���g������
#include <string>    // std::string�̂���

class CVector3; // �O���錾

class CModel
{
private:
    int m_Handle;

public:
    // �R���X�g���N�^�ŁAMODEL_ID�܂��̓t�@�C���p�X���󂯎��A���f�������[�h���܂�
    CModel(MODEL_ID id);

    // �f�X�g���N�^�ŁA���f���������I�ɃA�����[�h���܂�
    ~CModel();

    // ���f���n���h�����擾���邽�߂́A�B��̌��J���\�b�h
    int GetHandle() const;

    // --- ���f���f�[�^���̂ɑ΂��鑀��́A�����Ɏc���܂� ---
    bool CheckHitLine(const CVector3& startPos, const CVector3& endPos) const;
    CVector3 GetHitLinePosition(const CVector3& startPos, const CVector3& endPos) const;
    unsigned int GetMaterialDif(int material_index);
    void SetMaterialDif(int material_index, unsigned int color);

private:
    // �����ł̂ݎg���郍�[�h/�A�����[�h����
    void Load(const std::string& file_name);
    void Unload(void);
};