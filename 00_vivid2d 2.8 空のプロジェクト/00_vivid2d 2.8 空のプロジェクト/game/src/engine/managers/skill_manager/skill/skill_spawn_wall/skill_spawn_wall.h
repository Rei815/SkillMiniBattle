#pragma once
#include "../skill.h"
#include "../../../object_manager/object/object.h"

class CSkillSpawnWall : public CSkill
{
public:
    CSkillSpawnWall(void);
    ~CSkillSpawnWall(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(SKILL_ID skill_id);

    /*!
     *  @brief      更新
     */
    void        Update(void);

    /*!
     *  @brief      描画
     */
    void        Draw(void);

    /*!
     *  @brief      解放
     */
    void        Finalize(void);


    /*!
     *  @brief      アクション呼び出し
     */
    void Action(void);

    /*!
     *  @brief      アクション終了
     */
    void    ActionEnd(void);

protected:
    static const float  m_cool_time;
    static const float  m_duration_time;
    static const float  m_wall_spawn_distance;
    static const float  m_wall_spawn_height;
    static const float  m_effect_scale;

    std::shared_ptr<IEffect>            m_SkillEffect;
    std::shared_ptr<IObject>            m_WallObj;
};