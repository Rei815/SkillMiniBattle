#pragma once
#include "..\..\..\model\model.h"
#include "..\object.h"
#include "..\..\..\..\..\utility\utility.h"

class CBeltConveyorObject : public IObject
{
public:
	CBeltConveyorObject();
	~CBeltConveyorObject();


    /*!
     *  @brief      ������
     *
     */
    void    Initialize(OBJECT_ID id, const CTransform& transform);

    /*!
     *  @brief      �X�V
     */
    void    Update(void);

    /*!
     *  @brief      �`��
     */
    void    Draw(void);

    /*!
     *  @brief      ���
     */
    void    Finalize(void);

private:

    static const std::string m_model_file_name;
};