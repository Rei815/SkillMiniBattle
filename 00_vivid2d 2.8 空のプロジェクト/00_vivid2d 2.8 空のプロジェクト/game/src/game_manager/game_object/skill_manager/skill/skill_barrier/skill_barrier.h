#pragma once
#include "../skill.h"
#include "../../../effect_manager/effect/effect.h"
#include "../../../model_manager/model/model.h"

class CSkillBarrier : public CSkill
{
public:
    CSkillBarrier(void);
    ~CSkillBarrier(void);

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
     *  @brief      �v���C���[�̃Z�b�g
     */
    void    SetPlayer(CPlayer* player);

    /*!
     *  @brief      �A�N�V�����Ăяo��
     */
    void Action(void);

protected:
    static const float m_barrier_exist_time;
    static const float m_barrier_max_cool_time;
    static const float m_barrier_min_cool_time;
    static const std::string m_collider_model_file_name;

    CModel			    m_ColliderModel;
    IEffect*            m_Effect;
    CTimer              m_Timer;
    float               m_NowCoolTime;
};