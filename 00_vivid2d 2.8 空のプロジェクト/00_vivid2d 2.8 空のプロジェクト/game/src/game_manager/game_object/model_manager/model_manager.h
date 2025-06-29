#pragma once
#include <string>
#include <map>
#include "../model/model_id.h"

class CModelManager
{

public:
    /*!
     *  @brief      �C���X�^���X�̎擾
     *
     *  @return     �C���X�^���X
     */
    static CModelManager& GetInstance(void);

    // ... GetInstance()�ȂǁA�ȑO�̒�ĂƓ��� ...
    const std::string& GetModelFilePath(MODEL_ID id) const;
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
};