#pragma once
#include <string>
#include <map>
#include "../model/model_id.h"

class CModelManager
{
private:
    std::map<MODEL_ID, std::string> m_modelPaths;
    std::map<std::string, MODEL_ID> m_stringToIdMap;
    CModelManager();

public:
    // ... GetInstance()�ȂǁA�ȑO�̒�ĂƓ��� ...
    const std::string& GetModelFilePath(MODEL_ID id) const;
};