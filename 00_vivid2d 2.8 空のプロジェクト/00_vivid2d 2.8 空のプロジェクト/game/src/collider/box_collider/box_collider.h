#pragma once
#include "../../game_manager/game_object/model_manager/model/model.h"

class CBoxCollider
{
public:
	CBoxCollider();
	~CBoxCollider();

    /*!
     *  @brief      ������
     */
    void        Initialize(void);

    /*!
     *  @brief      �X�V
     */
    void        Update(void);

    /*!
     *  @brief      ���
     */
    void        Finalize(void);
private:
    static const std::string m_file_name;
    CModel          m_Model;
    CTransform      m_Transform;
};