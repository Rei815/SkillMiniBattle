#pragma once
#include "../skill.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../data_manager/data_manager.h"
#include "../../../gimmick_manager/gimmick/daruma_falldown_gimmick/daruma_falldown_gimmick.h"
#include "../../../effect_manager/effect_manager.h"

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

    /*!
     *  @brief      �A�N�V�����I��
     */
    void    ActionEnd(void);


protected:
    static const float       m_cool_time;
    static const float       m_duration_time;
    static const CVector3    m_EffectPosition;
    static const float       m_effect_scale;

    CPlayer*            m_Target;

    CDataManager&       dm = CDataManager::GetInstance();
    CUnitManager&       um = CUnitManager::GetInstance();

    CDaruma_FallDownGimmick* m_Gimmick;
    IEffect* m_Effect;
    IEffect* m_SkillEffect;
};