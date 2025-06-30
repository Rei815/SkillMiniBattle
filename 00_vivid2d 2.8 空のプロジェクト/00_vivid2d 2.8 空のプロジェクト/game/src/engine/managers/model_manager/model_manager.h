#pragma once
#include <string>
#include <map>
#include "model_id.h"

class CModelManager
{

public:
    /*!
     *  @brief      �C���X�^���X�̎擾
     *
     *  @return     �C���X�^���X
     */
    static CModelManager& GetInstance(void);

    const std::string& GetModelFilePath(MODEL_ID id) const;

    void LoadAllModels();    // �S�Ẵ��f�������[�h����
    void UnloadAllModels();  // �S�Ẵ��f�����A�����[�h����
    int GetModelHandle(MODEL_ID id) const; // ID����n���h�����擾����
private:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CModelManager(void);

    /*!
     *  @brief      �R�s�[�R���X�g���N�^
     *
     *  @param[in]  rhs     �I�u�W�F�N�g
     */
    CModelManager(const CModelManager& rhs);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CModelManager(void);

    /*!
     *  @brief      ������Z�q
     *
     *  @param[in]  rhs ����I�u�W�F�N�g
     *
     *  @return     ���g�̃I�u�W�F�N�g
     */
    CModelManager& operator=(const CModelManager& rhs);

    std::map<MODEL_ID, std::string> m_ModelPaths;
    std::map<std::string, MODEL_ID> m_StringToIdMap;
    // ���[�h�����n���h����ێ�����}�b�v
    std::map<MODEL_ID, int> m_ModelHandles;
};