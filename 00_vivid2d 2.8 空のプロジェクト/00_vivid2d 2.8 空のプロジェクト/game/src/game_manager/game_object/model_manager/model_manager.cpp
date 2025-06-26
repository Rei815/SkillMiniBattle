#include "model_manager.h"
// ������ ������CSV���[�_�[���C���N���[�h ������
#include "../../../utility/csv_loader/csv_loader.h" // ���Ȃ��̃v���W�F�N�g�̃p�X�ɍ��킹�Ă�������

CModelManager::CModelManager()
{
    // --- ����1�F�������enum�̑Ή��\����� ---
    m_stringToIdMap["PLAYER"] = MODEL_ID::PLAYER;
    // ...

    // --- ����2�FCSV���[�_�[�̃C���X�^���X���쐬 ---
    CCSVLoader csvLoader;
    csvLoader.Load("data/model_data.csv"); // model_data.csv��ǂݍ��܂���

    // --- �{�����FCSV�̍s�����[�v�ŉ񂵂āA�f�[�^��o�^���Ă��� ---
    // GetRows()��CSV�̍s�����擾���A���[�v����
    // ���w�b�_�[�s������̂ŁAi=1����n�߂�̂��ǂ��ł��傤
    for (int i = 1; i < csvLoader.GetRows(); ++i)
    {
        // 1���(cols=0)����AID������i"PLAYER"�Ȃǁj���擾
        std::string id_str = csvLoader.GetString(i, 0);

        // 2���(cols=1)����A�t�@�C���p�X��������擾
        std::string filepath = csvLoader.GetString(i, 1);

        // ������ID��enum��ID�ɕϊ�
        if (m_stringToIdMap.count(id_str))
        {
            MODEL_ID id = m_stringToIdMap.at(id_str);
            // �ŏI�I�ȃf�[�^�}�b�v�ɓo�^
            m_modelPaths[id] = filepath;
        }
    }
}

// GetModelFilePath���\�b�h�͈ȑO�̒�Ă̂܂܂�OK
const std::string& CModelManager::GetModelFilePath(MODEL_ID id) const
{
    return m_modelPaths.at(id);
}