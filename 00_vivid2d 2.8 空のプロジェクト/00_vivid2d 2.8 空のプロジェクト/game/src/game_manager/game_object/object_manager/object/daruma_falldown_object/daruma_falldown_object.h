#pragma once
#include "../../../model_manager/model/model.h"
#include "..\object.h"
#include "..\..\..\..\..\utility\utility.h"
enum class DARUMA_FALLDOWN_OBJECT_STATE
{
    WAIT,
    FALL,
};
class CDaruma_FallDownObject : public IObject
{
public:
    CDaruma_FallDownObject();
    ~CDaruma_FallDownObject();

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

private:
    static const float                     m_start_height;
    static const float                     m_remove_height;
    static const float                     m_invisible_alpha;
    static const std::string               m_file_name_list[];
    float                                  m_FallSpeed;
    DARUMA_FALLDOWN_OBJECT_STATE           m_Daruma_FallDownObjectState;
    CTimer                                 m_Timer;
};