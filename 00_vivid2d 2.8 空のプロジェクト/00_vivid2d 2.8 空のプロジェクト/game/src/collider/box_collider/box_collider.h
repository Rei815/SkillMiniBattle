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

};