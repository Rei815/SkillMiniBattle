#pragma once
#include "../../../model_manager/model/model.h"
#include "..\object.h"
#include "..\..\..\..\..\utility\utility.h"

class CMazeStage : public IObject
{
public:
    CMazeStage();
    ~CMazeStage();

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

    static const std::string m_file_name;

};