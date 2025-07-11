#include "model_manager.h"
#include "../../utility/csv_loader/csv_loader.h"

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
    // �ǂݍ��񂾃p�X�������ɁA�S�Ẵ��f�������[�h����
    LoadAllModels();
}

// GetModelFilePath���\�b�h�͈ȑO�̒�Ă̂܂܂�OK
const std::string& CModelManager::GetModelFilePath(MODEL_ID id) const
{
    return m_ModelPaths.at(id);
}
void CModelManager::LoadAllModels()
{
    // m_ModelPaths�ɓo�^����Ă���S�Ẵ��f�������[�v���ă��[�h
    for (const auto& pair : m_ModelPaths)
    {
        MODEL_ID id = pair.first;
        const std::string& path = pair.second;

        // ���f�������[�h���A�n���h�����擾
        int handle = MV1LoadModel(path.c_str());

        // �擾�����n���h����m_ModelHandles�}�b�v�ɕۑ�
        m_ModelHandles[id] = handle;
    }
}

void CModelManager::UnloadAllModels()
{
    // ���[�h�����S�Ẵ��f���n���h�������[�v���ĉ��
    for (const auto& pair : m_ModelHandles)
    {
        MV1DeleteModel(pair.second);
    }
    // �}�b�v���N���A
    m_ModelHandles.clear();
}

int CModelManager::GetModelHandle(MODEL_ID id) const
{
    // �}�b�v�Ɏw�肳�ꂽID�����݂��邩�`�F�b�N
    if (m_ModelHandles.count(id))
    {
        // ���݂���΁A�Ή�����n���h����Ԃ�
        return m_ModelHandles.at(id);
    }

    // ���݂��Ȃ��ꍇ�̓G���[�Ƃ���-1��Ԃ�
    return VIVID_DX_ERROR;
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
    // �A�v���P�[�V�����I�����ɁA���[�h�����S�Ẵ��f�����������
    UnloadAllModels();
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
