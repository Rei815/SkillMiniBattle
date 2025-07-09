#pragma once
#include "../skill.h"
#include "../../../data_manager/data_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../object_manager/object_manager.h"

class DarumaFallDownGimmickComponent;
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
    static const float          m_cool_time;
    static const float          m_duration_time;
    static const CVector3       m_EffectPosition;
    static const float          m_effect_scale;

    std::shared_ptr<CGameObject>    m_Target;

    CDataManager&       dm = CDataManager::GetInstance();
    CObjectManager&     om = CObjectManager::GetInstance();

    std::shared_ptr<DarumaFallDownGimmickComponent> m_Gimmick;
    std::shared_ptr<IEffect> m_Effect;
    std::shared_ptr<IEffect> m_SkillEffect;
};