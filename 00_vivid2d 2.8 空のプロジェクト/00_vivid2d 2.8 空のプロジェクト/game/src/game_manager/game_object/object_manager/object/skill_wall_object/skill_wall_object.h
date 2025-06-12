#pragma once
#include "../../../model/model.h"
#include "..\object.h"
#include "..\..\..\..\..\utility\utility.h"

class CSkillWallObject : public IObject
{
public:
    CSkillWallObject();
    ~CSkillWallObject();

    /*!
     *  @brief      ‰Šú‰»
     *
     */
    void    Initialize(OBJECT_ID id, const CTransform& transform);

    /*!
     *  @brief      XV
     */
    void    Update(void);

    /*!
     *  @brief      •`‰æ
     */
    void    Draw(void);

    /*!
     *  @brief      ‰ğ•ú
     */
    void    Finalize(void);

private:

    static const std::string  m_model_file_name;
    static const unsigned int m_model_color;

};