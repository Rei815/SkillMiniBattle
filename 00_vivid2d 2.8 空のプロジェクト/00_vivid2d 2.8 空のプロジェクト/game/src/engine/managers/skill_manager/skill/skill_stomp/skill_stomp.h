#pragma once
#include "../skill.h"
#include "../../../../../engine/managers/bullet_manager/bullet/bullet.h"
#include "../../../../managers/effect_manager/effect/effect.h"
class CSkillStomp : public CSkill
{
public:
    CSkillStomp(void);
    ~CSkillStomp(void);

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
    void Action();

    /*!
     *  @brief      アクション終了
     */
    void    ActionEnd(void);

private:
    static const float              m_cool_time;    //!< クールタイム
    static const float              m_effect_scale; //!< エフェクト拡大率
        
    std::shared_ptr<IBullet>        m_Bullet;       //!< 弾
    std::shared_ptr<IEffect>        m_SkillEffect;  //!< エフェクト
};