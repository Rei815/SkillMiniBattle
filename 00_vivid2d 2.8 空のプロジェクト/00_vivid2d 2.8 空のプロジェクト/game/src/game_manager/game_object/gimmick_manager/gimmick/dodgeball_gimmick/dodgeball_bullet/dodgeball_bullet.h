#pragma once
#include "../../../../model_manager/model/model.h"
class CDodgeBallBullet
{
public:
	CDodgeBallBullet();
	~CDodgeBallBullet();

    /*!
     *  @brief      ‰Šú‰»
     *
     */
    void    Initialize(void);

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

    static const std::string   m_file_name;
};