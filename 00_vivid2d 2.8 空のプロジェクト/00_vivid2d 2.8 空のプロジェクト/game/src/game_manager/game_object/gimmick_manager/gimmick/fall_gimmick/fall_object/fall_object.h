#pragma once
#include "../../../../model_manager/model/model.h"
#include "mark_id.h"
class CFallObject
{
public:
	CFallObject();
	~CFallObject();

    /*!
     *  @brief      ‰Šú‰»
     *
     */
    void    Initialize(MARK_ID id);

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
	CModel			m_Model;
	CTransform		m_Transform;
    std::string     m_FileName;
};