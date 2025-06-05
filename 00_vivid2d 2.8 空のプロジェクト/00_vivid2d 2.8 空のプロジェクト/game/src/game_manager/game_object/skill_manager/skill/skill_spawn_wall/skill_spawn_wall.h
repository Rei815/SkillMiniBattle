#pragma once
#include "../skill.h"
#include "../../../object_manager/object/object.h"

class CSkillSpawnWall : public CSkill
{
public:
    CSkillSpawnWall(void);
    ~CSkillSpawnWall(void);

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
    void Action(void);

    /*!
     *  @brief      �A�N�V�����I��
     */
    void    ActionEnd(void);

protected:
    static const float  m_cool_time;
    static const float  m_duration_time;
    static const float  m_wall_spawn_distance;
    static const float  m_effect_scale;

    IEffect*            m_SkillEffect;
    std::shared_ptr<IObject>            m_WallObj;
};