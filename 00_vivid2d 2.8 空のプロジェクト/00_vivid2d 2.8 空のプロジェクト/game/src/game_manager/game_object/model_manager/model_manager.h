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
    // ... GetInstance()‚È‚ÇAˆÈ‘O‚Ì’ñˆÄ‚Æ“¯‚¶ ...
    const std::string& GetModelFilePath(MODEL_ID id) const;
};