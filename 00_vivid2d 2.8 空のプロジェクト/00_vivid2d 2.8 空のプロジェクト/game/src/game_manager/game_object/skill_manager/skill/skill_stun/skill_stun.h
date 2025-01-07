#pragma once
#include "../skill.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../data_manager/data_manager.h"

class CSkillStun : public CSkill
{
public:
    CSkillStun(void);
    ~CSkillStun(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(SKILL_ID skill_id);

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
    void        Action(void);

protected:
    static const float m_cool_time;
    static const float m_active_time;

    SKILL_STATE         m_State;
    CTimer              m_Timer;

    CUnitManager& um = CUnitManager::GetInstance();
    CDataManager& dm = CDataManager::GetInstance();
};