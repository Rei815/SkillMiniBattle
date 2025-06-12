#include "effect_manager.h"
#include "effect/hit_effect/hit_effect.h"
#include "effect/jump_effect/jump_effect.h"
#include "effect/shock_wave_effect/shock_wave_effect.h"
#include "effect/forecast_line_effect/forecast_line_effect.h"
#include "effect/barrier_effect/barrier_effect.h"
#include "effect/floating_effect/floating_effect.h"
#include "effect/gravity_area_effect/gravity_area_effect.h"
#include "effect/strong_wind_effect/strong_wind_effect.h"
#include "effect/skill_star_effect/skill_star_effect.h"
#include "effect/ogre_control_effect/ogre_control_effect.h"
#include "effect/debuff_effect/debuff_effect.h"
#include "effect/resurrect_effect/resurrect_effect.h"
 /*
  *  インスタンスの取得
  */
CEffectManager&
CEffectManager::
GetInstance(void)
{
    static CEffectManager instance;

    return instance;
}

/*
 *  初期化
 */
void
CEffectManager::
Initialize(void)
{
    m_EffectList.clear();
    vivid::effekseer::SetUseEffectListFlag(false);
}

/*
 *  更新
 */
void
CEffectManager::
Update(void)
{
    if (m_EffectList.empty()) return;

    EFFECT_LIST::iterator it = m_EffectList.begin();

    while (it != m_EffectList.end())
    {
        std::shared_ptr<IEffect> effect = *it;

        effect->Update();

        if (!effect->IsActive())
        {
            effect->Finalize();

            it = m_EffectList.erase(it);

            continue;
        }

        ++it;
    }
}

/*
 *  描画
 */
void
CEffectManager::
Draw(void)
{
    if (m_EffectList.empty()) return;

    EFFECT_LIST::iterator it = m_EffectList.begin();

    while (it != m_EffectList.end())
    {
        (*it)->Draw();

        ++it;
    }
}

/*
 *  解放
 */
void
CEffectManager::
Finalize(void)
{
    if (m_EffectList.empty()) return;

    EFFECT_LIST::iterator it = m_EffectList.begin();

    while (it != m_EffectList.end())
    {
        (*it)->Finalize();

        ++it;
    }

    m_EffectList.clear();
}

std::shared_ptr<IEffect> CEffectManager::Create(EFFECT_ID id, const CVector3& pos, const float scale)
{
    std::shared_ptr<IEffect> effect = CreateClass(id);


    if (!effect) return nullptr;

    effect->Initialize(pos, scale);

    m_EffectList.emplace_back(effect);

    return effect;
}

std::shared_ptr<IEffect> CEffectManager::Create(EFFECT_ID id, const CVector3& pos, const CVector3& rot)
{
    std::shared_ptr<IEffect> effect = CreateClass(id);

    if (!effect) return nullptr;

    effect->Initialize(pos,rot);

    m_EffectList.emplace_back(effect);

    return effect;
}

std::shared_ptr<IEffect> CEffectManager::Create(EFFECT_ID id, const CVector3& pos, const CVector3& rot, const float scale)
{
    std::shared_ptr<IEffect> effect = CreateClass(id);

    if (!effect) return nullptr;

    effect->Initialize(pos, rot, scale);

    m_EffectList.emplace_back(effect);

    return effect;
}

std::shared_ptr<IEffect> CEffectManager::Create(EFFECT_ID id, const CVector3& pos, const CVector3& rot, const CVector3& scale)
{
    std::shared_ptr<IEffect> effect = CreateClass(id);

    if (!effect) return nullptr;

    effect->Initialize(pos, rot, scale);

    m_EffectList.emplace_back(effect);

    return effect;
}

void CEffectManager::PauseAllEffect()
{
    if (m_EffectList.empty()) return;

    EFFECT_LIST::iterator it = m_EffectList.begin();

    while (it != m_EffectList.end())
    {
        std::shared_ptr<IEffect> effect = *it;

        effect->Pause();

        ++it;
    }

}

void CEffectManager::ResumeAllEffect()
{
    if (m_EffectList.empty()) return;

    EFFECT_LIST::iterator it = m_EffectList.begin();

    while (it != m_EffectList.end())
    {
        std::shared_ptr<IEffect> effect = *it;

        effect->Resume();

        ++it;
    }


}

std::shared_ptr<IEffect> CEffectManager::CreateClass(EFFECT_ID id)
{
    std::shared_ptr<IEffect> effect = nullptr;

    switch (id)
    {
    case EFFECT_ID::HIT:                    effect = std::make_shared<CHitEffect>();            break;
    case EFFECT_ID::JUMP:                   effect = std::make_shared<CJumpEffect>();           break;
    case EFFECT_ID::SHOCK_WAVE:             effect = std::make_shared<CShockWaveEffect>();      break;
    case EFFECT_ID::FORECAST_LINE:          effect = std::make_shared<CForecastLineEffect>();   break;
    case EFFECT_ID::BARRIER:                effect = std::make_shared<CBarrierEffect>();        break;
    case EFFECT_ID::FLOATING:               effect = std::make_shared<CFloatingEffect>();       break;
    case EFFECT_ID::GRAVITY_AREA:           effect = std::make_shared<CGravityAreaEffect>();    break;
    case EFFECT_ID::STRONG_WIND:            effect = std::make_shared<CStrongWindEffect>();     break;
    case EFFECT_ID::SKILL_STAR:             effect = std::make_shared<CSkillStarEffect>();      break;
    case EFFECT_ID::OGRE_CONTROL:           effect = std::make_shared<COgreControlEffect>();    break;
    case EFFECT_ID::DEBUFF:                 effect = std::make_shared<CDebuffEffect>();         break;
    case EFFECT_ID::RESURRECT:              effect = std::make_shared<CResurrectEffect>();      break;
    }
    return effect;
}

/*
 *  コンストラクタ
 */
CEffectManager::
CEffectManager(void)
{
}

/*
 *  コピーコンストラクタ
 */
CEffectManager::
CEffectManager(const CEffectManager& rhs)
{
    (void)rhs;
}

/*
 *  デストラクタ
 */
CEffectManager::
~CEffectManager(void)
{
}

/*
 *  代入演算子
 */
CEffectManager&
CEffectManager::
operator=(const CEffectManager& rhs)
{
    (void)rhs;

    return *this;
}
