#pragma once
#include "../../../model_manager/model/model.h"
#include "mark_id.h"
#include "..\object.h"
#include "..\..\..\..\..\utility\utility.h"
enum class FALL_OBJECT_STATE
{
    WAIT,
    FALL,
};
class CFallObject : public IObject
{
public:
    CFallObject();
    ~CFallObject();

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
     *  @brief      ID�擾
     *
     *  @return     �}�[�NID
     */
    MARK_ID         GetID(void);

private:
    enum class STATE
    {
        WAIT,
        ACTIVE,
    };
    static const std::string    m_file_name_list[];
    MARK_ID                     m_MarkID;
};