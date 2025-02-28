#include "skill_strong_wind.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../effect_manager/effect_manager.h"


const float CSkillStrongWind::m_wind_strength = 0.15f;
const float CSkillStrongWind::m_cool_time = 5.0f;
const float CSkillStrongWind::m_duration_time = 5.0f;
const float CSkillStrongWind::m_effect_scale = 2.0f;
const int   CSkillStrongWind::m_se_volume = 10000;

CSkillStrongWind::CSkillStrongWind(void)
	:CSkill(SKILL_CATEGORY::ACTIVE ,m_duration_time, m_cool_time)
	,m_Effect(nullptr)
	,m_SkillEffect(nullptr)
{

}

CSkillStrongWind::~CSkillStrongWind(void)
{

}

/*!
 *  @brief      初期化
 */
void
CSkillStrongWind::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

/*!
 *  @brief      更新
 */
void
CSkillStrongWind::
Update(void)
{
	CSkill::Update();
	CUnitManager::UNIT_LIST unitList = CUnitManager::GetInstance().GetUnitList();
	CUnitManager::UNIT_LIST::iterator it = unitList.begin();
	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;

	case SKILL_STATE::ACTIVE:
		while (it != unitList.end())
		{
			IUnit* unit = (*it);

			if (unit->GetUnitID() != m_Player->GetUnitID())
				unit->AddAffectedVelocity(CVector3(0.0f, 0.0f, -m_wind_strength));

			++it;
		}
		break;

	case SKILL_STATE::COOLDOWN:
		break;
	}
}

/*!
 *  @brief      描画
 */
void
CSkillStrongWind::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CSkillStrongWind::
Finalize(void)
{
	CSkill::Finalize();


}

/*!
 *  @brief      アクション呼び出し
 */
void
CSkillStrongWind::
Action(void)
{
	if (m_State != SKILL_STATE::WAIT) return;

	CSoundManager::GetInstance().Play_SE(SE_ID::STRONG_WIND, false);
	CSoundManager::GetInstance().SetSEVolume(SE_ID::STRONG_WIND, m_se_volume);

	CVector3 effectPosition = CVector3().ZERO;

	m_Effect = CEffectManager::GetInstance().Create(EFFECT_ID::STRONG_WIND, effectPosition, CVector3(), 5.0f);
	m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, CVector3().ZERO, CVector3(), m_effect_scale);
	m_SkillEffect->SetParent(m_Player);

	m_State = SKILL_STATE::ACTIVE;
}

/*!
 *  @brief      アクション終了
 */
void
CSkillStrongWind::
ActionEnd(void)
{
	//エフェクトを消す
	if (m_Effect != nullptr)
	{
		m_Effect->SetActive(false);
		m_Effect = nullptr;
	}
	if (m_SkillEffect != nullptr)
	{
		m_SkillEffect->SetActive(false);
		m_SkillEffect = nullptr;
	}

	for (int i = 10000; i > 0; i--)
	{
		CSoundManager::GetInstance().SetSEVolume(SE_ID::STRONG_WIND, i);
	}
}