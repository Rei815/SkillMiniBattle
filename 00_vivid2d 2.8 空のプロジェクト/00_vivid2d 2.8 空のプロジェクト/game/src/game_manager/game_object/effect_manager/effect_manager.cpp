#include "effect_manager.h"
#include "effect/destroy_effect/destroy_effect.h"
#include "effect/hit_effect/hit_effect.h"
#include "effect/jump_effect/jump_effect.h"
#include "effect/dust_cloud_effect/dust_cloud_effect.h"
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
  *  �C���X�^���X�̎擾
  */
CEffectManager&
CEffectManager::
GetInstance(void)
{
    static CEffectManager instance;

    return instance;
}

/*
 *  ������
 */
void
CEffectManager::
Initialize(void)
{
    m_EffectList.clear();
    vivid::effekseer::SetUseEffectListFlag(false);
}

/*
 *  �X�V
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
 *  �`��
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
 *  ���
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

IEffect* CEffectManager::Create(EFFECT_ID id, const CVector3& pos, const float scale)
{
    IEffect* effect = CreateClass(id);


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

void CEffectManager::PauseAllEffect()
{
    if (m_EffectList.empty()) return;

    EFFECT_LIST::iterator it = m_EffectList.begin();

    while (it != m_EffectList.end())
    {
        IEffect* effect = (IEffect*)(*it);

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
        IEffect* effect = (IEffect*)(*it);

        effect->Resume();

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
    case EFFECT_ID::JUMP:                   effect = new CJumpEffect();             break;
    case EFFECT_ID::DUST_CLOUD:             effect = new CDustCloudEffect();        break;
    case EFFECT_ID::SHOCK_WAVE:             effect = new CShockWaveEffect();        break;
    case EFFECT_ID::FORECAST_LINE:          effect = new CForecastLineEffect();     break;
    case EFFECT_ID::BARRIER:          effect = new CBarrierEffect();     break;
    case EFFECT_ID::FLOATING:               effect = new CFloatingEffect();         break;
    case EFFECT_ID::GRAVITY_AREA:           effect = new CGravityAreaEffect();      break;
    case EFFECT_ID::STRONG_WIND:            effect = new CStrongWindEffect();       break;
    case EFFECT_ID::SKILL_STAR:             effect = new CSkillStarEffect();        break;
    case EFFECT_ID::OGRE_CONTROL:           effect = new COgreControlEffect();      break;
    case EFFECT_ID::DEBUFF:                 effect = new CDebuffEffect();           break;
    case EFFECT_ID::RESURRECT:              effect = new CResurrectEffect();        break;
    }
    return effect;
}

/*
 *  �R���X�g���N�^
 */
CEffectManager::
CEffectManager(void)
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
CEffectManager::
CEffectManager(const CEffectManager& rhs)
{
    (void)rhs;
}

/*
 *  �f�X�g���N�^
 */
CEffectManager::
~CEffectManager(void)
{
}

/*
 *  ������Z�q
 */
CEffectManager&
CEffectManager::
operator=(const CEffectManager& rhs)
{
    (void)rhs;

    return *this;
}
