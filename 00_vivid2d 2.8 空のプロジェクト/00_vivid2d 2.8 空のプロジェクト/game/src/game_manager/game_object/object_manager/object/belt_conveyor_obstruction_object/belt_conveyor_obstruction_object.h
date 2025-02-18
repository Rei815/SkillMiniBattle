#pragma once
#include "..\..\..\model_manager\model\model.h"
#include "..\object.h"

enum class OBSTRUCTION_ID
{
	DOWN_1,
	DOWN_2,
	DOWN_3,
    UP_1,
    UP_2,
    UP_3,

	MAX,
};

class CBeltConveyorObstructionObject : public IObject
{
public:
    CBeltConveyorObstructionObject();
    ~CBeltConveyorObstructionObject();

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


    /*!
     *  @brief      ���
     * 
     *  @param[in]  id      �Z�b�g�����Q���^�C�v��ID
     */
    void    SetObstructionType(OBSTRUCTION_ID id);

private:
    static const std::string m_model_file_name_list[(int)OBSTRUCTION_ID::MAX];

    OBSTRUCTION_ID m_NowObstructionID;
};