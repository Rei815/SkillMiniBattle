#pragma once
#include "../skill.h"

class CPunchUp : public CSkill
{
public:
    CPunchUp(void);
    ~CPunchUp(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(CPlayer* player);

    /*!
     *  @brief      �X�V
     */
    void        Update(void);

    /*!
     *  @brief      �`��
     */
    void        Draw(void);

    /*!
     *  @brief      ���
     */
    void        Finalize(void);


    /*!
     *  @brief      �A�N�V�����Ăяo��
     */
    void Action(void);

protected:
    static const float speed_up_rate;
};