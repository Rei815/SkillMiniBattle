#pragma once
#include "../../../model_manager/model/model.h"
#include "mark_id.h"
#include "..\object.h"

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
    void    Initialize(OBJECT_ID id, const CVector3& position);

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
     *  @brief      �A�N�e�B�u�t���O�擾
     *
     *  @return     �A�N�e�B�u�t���O
     */
    bool            GetActive(void);

    /*!
     *  @brief      �A�N�e�B�u�t���O�ݒ�
     *
     *  @param[in]  active  �A�N�e�B�u�t���O
     */
    void            SetActive(bool active);

    /*!
     *  @brief      ID�擾
     *
     *  @return     �}�[�NID
     */
    MARK_ID         GetID(void);

    /*!
     *  @brief      ��Ԑݒ�
     *
     *  @param[in]  state  �t�H�[���I�u�W�F�N�g�̏��
     */
    void            SetState(FALL_OBJECT_STATE active);

private:
    static const float  m_fall_speed;
    float               m_FallSpeed;
    FALL_OBJECT_STATE   m_FallObjectState;
    MARK_ID             m_MarkID;
};