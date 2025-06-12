#pragma once
#include "../../../model/model.h"
#include "..\object.h"
#include "..\..\..\..\..\utility\utility.h"
enum class OGRE_OBJECT_STATE
{
    WAIT,
    FALL,
};
class COgreObject : public IObject
{
public:
    COgreObject();
    ~COgreObject();

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

private:
    static const float                     m_start_height;
    static const float                     m_return_height;
    static const float                     m_invisible_alpha;
    static const std::string               m_file_name;
    float                                  m_FallSpeed;
    OGRE_OBJECT_STATE           m_Daruma_FallDownObjectState;
    CTimer                                 m_Timer;
};