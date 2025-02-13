#include "effect_manager.h"
#include "effect/destroy_effect/destroy_effect.h"
#include "effect/hit_effect/hit_effect.h"
#include "effect/hit_invincible_effect/hit_invincible_effect.h"
#include "effect/jump_effect/jump_effect.h"
#include "effect/dust_cloud_effect/dust_cloud_effect.h"
#include "effect/emergency_effect/emergency_effect.h"
#include "effect/shock_wave_effect/shock_wave_effect.h"
#include "effect/player_bullet_effect/player_bullet_effect.h"
#include "effect/enemy_bullet_effect/enemy_bullet_effect.h"
#include "effect/forecast_line_effect/forecast_line_effect.h"
#include "effect/skill_barrier_effect/skill_barrier_effect.h"
#include "effect/floating_effect/floating_effect.h"
#include "effect/gravity_area_effect/gravity_area_effect.h"
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
        IEffect* effect = (IEffect*)(*it);

        effect->Update();

        if (!effect->GetActive())
        {
            effect->Finalize();

            delete effect;

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

        delete (*it);

        ++it;
    }

    m_EffectList.clear();
}

/*
 *  エフェクト生成
 */
IEffect*
CEffectManager::
Create(EFFECT_ID id, const CVector3& pos)
{
    IEffect* effect = CreateClass(id);

    if (!effect) return nullptr;

    effect->Initialize(pos);

     m_EffectList.push_back(effect);
    return effect;
}

IEffect* CEffectManager::Create(EFFECT_ID id, const CVector3& pos, const float scale)
{
    IEffect* effect = nullptr;


    if (!effect) return nullptr;

    effect->Initialize(pos, scale);

    m_EffectList.push_back(effect);

    return effect;
}

IEffect* CEffectManager::Create(EFFECT_ID id, const CVector3& pos, const CVector3& rot)
{
    IEffect* effect = CreateClass(id);

    if (!effect) return nullptr;

    effect->Initialize(pos,rot);

    m_EffectList.push_back(effect);

    return effect;
}

IEffect* CEffectManager::Create(EFFECT_ID id, const CVector3& pos, const CVector3& rot, const float scale)
{
    IEffect* effect = CreateClass(id);

    if (!effect) return nullptr;

    effect->Initialize(pos, rot, scale);

    m_EffectList.push_back(effect);

    return effect;
}

IEffect* CEffectManager::Create(EFFECT_ID id, const CVector3& pos, const CVector3& rot, const CVector3& scale)
{
    IEffect* effect = CreateClass(id);

    if (!effect) return nullptr;

    effect->Initialize(pos, rot, scale);

    m_EffectList.push_back(effect);

    return effect;
}

/*
 *  エフェクト生成
 */
IEffect*
CEffectManager::
Create(EFFECT_ID id, const vivid::Vector2& pos, unsigned int color, float rotation)
{
    IEffect* effect = nullptr;

    switch (id)
    {
    case EFFECT_ID::EMERGENCY:           effect = new CEmergencyEffect();        break;
    }

    if (!effect) return nullptr;

    effect->Initialize(pos, color, rotation);

    m_EffectList.push_back(effect);
    return effect;
}

void CEffectManager::SetParentPosition(EFFECT_ID effectID, CVector3& parentPos)
{
    if (m_EffectList.empty()) return;

    EFFECT_LIST::iterator it = m_EffectList.begin();

    while (it != m_EffectList.end())
    {
        IEffect* effect = (IEffect*)(*it);


        if (effect->GetEffectID() == effectID)
        {
            effect->SetParentPosition(parentPos);

            return;
        }

        ++it;
    }

}

IEffect* CEffectManager::CreateClass(EFFECT_ID id)
{
    IEffect* effect = nullptr;

    switch (id)
    {
    case EFFECT_ID::DESTROY:                effect = new CDestroyEffect();          break;
    case EFFECT_ID::HIT:                    effect = new CHitEffect();              break;
    case EFFECT_ID::HIT_INVINCBLE:          effect = new CHitInvincibleEffect();    break;
    case EFFECT_ID::JUMP:                   effect = new CJumpEffect();             break;
    case EFFECT_ID::DUST_CLOUD:             effect = new CDustCloudEffect();        break;
    case EFFECT_ID::SHOCK_WAVE:             effect = new CShockWaveEffect();        break;
    case EFFECT_ID::PLAYER_BULLET:          effect = new CPlayerBulletEffect();     break;
    case EFFECT_ID::ENEMY_BULLET:           effect = new CEnemyBulletEffect();      break;
    case EFFECT_ID::FORECAST_LINE:          effect = new CForecastLineEffect();     break;
    case EFFECT_ID::SKILL_BARRIER:          effect = new CSkillBarrierEffect();     break;
    case EFFECT_ID::FLOATING:               effect = new CFloatingEffect();         break;
    case EFFECT_ID::GRAVITY_AREA:               effect = new CGravityAreaEffect();     break;
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
