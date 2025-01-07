#pragma once
#include "../skill.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../data_manager/data_manager.h"
#include "../../../gimmick_manager/gimmick/daruma_falldown_gimmick/daruma_falldown_gimmick.h"

class CSkillOgreControl : public CSkill
{
public:
    CSkillOgreControl(void);
    ~CSkillOgreControl(void);

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

    CPlayer*            m_Target;
    SKILL_STATE         m_State;
    CTimer              m_Timer;

    CDataManager&       dm = CDataManager::GetInstance();
    CUnitManager&       um = CUnitManager::GetInstance();

    CDaruma_FallDownGimmick& dg = CDaruma_FallDownGimmick();
};