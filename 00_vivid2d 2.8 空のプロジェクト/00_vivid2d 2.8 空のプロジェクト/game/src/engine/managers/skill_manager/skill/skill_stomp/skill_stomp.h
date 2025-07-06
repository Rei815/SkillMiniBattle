#pragma once
#include "../skill.h"
#include "../../../../../engine/core/game_object/game_object.h"
#include "../../../../managers/effect_manager/effect/effect.h"
class CSkillStomp : public CSkill
{
public:
    CSkillStomp(void);
    ~CSkillStomp(void);

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
    void Action();

    /*!
     *  @brief      �A�N�V�����I��
     */
    void    ActionEnd(void);

private:
    static const float              m_cool_time;    //!< �N�[���^�C��
    static const float              m_effect_scale; //!< �G�t�F�N�g�g�嗦

    std::shared_ptr<CGameObject>    m_GameObject;   //!< �G���e�B�e�B
    std::shared_ptr<IEffect>        m_SkillEffect;  //!< �G�t�F�N�g
};