
#pragma once
#include "..\gimmick.h"
#include <list>
class CFallGimmick : public CGimmick
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     */
    CFallGimmick();

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CFallGimmick(void);

    /*!
     *  @brief      ������
     *
     */
    void    Initialize(IObject* object);

    /*!
     *  @brief      ������
     *  @param[in]  object          �I�u�W�F�N�g�̃|�C���^
     *  @param[in]  delayFrame      �x���t���[��
     *
     */
    void    Initialize(IObject* object, int delayFrame);

    /*!
     *  @brief      �X�V
     */
    void    Update(void);

    /*!
     *  @brief      ���
     */
    void    Finalize(void);

    void    SetSwitch(bool sw);
private:
    static const float  m_fall_speed;

};
