#pragma once
#include "..\..\..\utility\utility.h"
#include "../game_object.h"
class CBeltConveyorObject : public CGameObject
{
public:
	CBeltConveyorObject();
	~CBeltConveyorObject();


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

    static const std::string m_model_file_name;
};