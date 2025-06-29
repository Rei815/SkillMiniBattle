#include "model_manager.h"
// ������ ������CSV���[�_�[���C���N���[�h ������
#include "../../../utility/csv_loader/csv_loader.h" // ���Ȃ��̃v���W�F�N�g�̃p�X�ɍ��킹�Ă�������

 /*
  *  �C���X�^���X�̎擾
  */
CModelManager& CModelManager::GetInstance(void)
{
    static CModelManager instance;

    return instance;
}

CModelManager::CModelManager()
{
    // --- ����1�F�������enum�̑Ή��\����� ---
    m_StringToIdMap["PLAYER"] = MODEL_ID::PLAYER;
    m_StringToIdMap["BULLET"] = MODEL_ID::BULLET;
    m_StringToIdMap["CANNON"] = MODEL_ID::CANNON;
    m_StringToIdMap["BARRIER"] = MODEL_ID::BARRIER;
    m_StringToIdMap["OGRE"] = MODEL_ID::OGRE;
    m_StringToIdMap["FALLOUT_FLOOR"] = MODEL_ID::FALLOUT_FLOOR;
    m_StringToIdMap["DODGEBALL_STAGE"] = MODEL_ID::DODGEBALL_STAGE;
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
    // ...

    // --- ����2�FCSV���[�_�[�̃C���X�^���X���쐬 ---
    CCSVLoader csvLoader;
    csvLoader.Load("data/model_data.csv"); // model_data.csv��ǂݍ��܂���

    for (int i = 0; i < csvLoader.GetRows(); ++i)
    {
        // 1���(cols=0)����AID������i"PLAYER"�Ȃǁj���擾
        std::string id_str = csvLoader.GetString(i, 0);

        // 2���(cols=1)����A�t�@�C���p�X��������擾
        std::string filepath = csvLoader.GetString(i, 1);

        // ������ID��enum��ID�ɕϊ�
        if (m_StringToIdMap.count(id_str))
        {
            MODEL_ID id = m_StringToIdMap.at(id_str);
            // �ŏI�I�ȃf�[�^�}�b�v�ɓo�^
            m_ModelPaths[id] = filepath;
        }
    }
}

// GetModelFilePath���\�b�h�͈ȑO�̒�Ă̂܂܂�OK
const std::string& CModelManager::GetModelFilePath(MODEL_ID id) const
{
    return m_ModelPaths.at(id);
}
/*
 *  �R���X�g���N�^
 */
CModelManager::
CModelManager(void)
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
CModelManager::
CModelManager(const CModelManager& rhs)
{
    (void)rhs;
}

/*
 *  �f�X�g���N�^
 */
CModelManager::
~CModelManager(void)
{
}

/*
 *  ������Z�q
 */
CModelManager&
CModelManager::
operator=(const CModelManager& rhs)
{
    (void)rhs;

    return *this;
}
