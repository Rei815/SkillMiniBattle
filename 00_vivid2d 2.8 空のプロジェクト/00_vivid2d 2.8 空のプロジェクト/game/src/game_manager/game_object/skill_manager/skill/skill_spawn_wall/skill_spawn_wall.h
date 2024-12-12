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

protected:
    static const float  m_spawn_cool_time;
    static const float  m_wall_exist_time;
    static const float  m_wall_spawn_distance;

    CTimer              m_Timer;

    IObject*            m_WallObj;
};