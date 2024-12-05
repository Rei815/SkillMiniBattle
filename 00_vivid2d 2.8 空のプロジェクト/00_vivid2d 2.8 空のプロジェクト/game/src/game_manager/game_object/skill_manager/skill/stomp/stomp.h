#pragma once
#pragma once
#include "../skill.h"

class CStomp : public CSkill
{
public:
    CStomp(void);
    ~CStomp(void);

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
    void Action(UNIT_CATEGORY category);

protected:
    static const float  m_floating_time;

    CTimer              m_Timer;
    CShot*              m_Shot;
};