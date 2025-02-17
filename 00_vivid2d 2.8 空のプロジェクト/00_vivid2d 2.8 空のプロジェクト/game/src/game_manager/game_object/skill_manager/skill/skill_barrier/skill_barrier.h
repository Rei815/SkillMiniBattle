#pragma once
#include "../skill.h"
#include "../../../effect_manager/effect/effect.h"
#include "../../../model_manager/model/model.h"
#include "../../../effect_manager/effect_manager.h"

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

    /*!
     *  @brief      �A�N�V�����I��
     */
    void ActionEnd(void);

protected:
    static const float m_duration_time;
    static const float m_cool_time;
    static const std::string m_collider_model_file_name;
    static const float m_effect_scale;

    CModel			    m_ColliderModel;
    IEffect*            m_Effect;
    IEffect*            m_SkillEffect;
};