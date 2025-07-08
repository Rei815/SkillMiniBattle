#include "skill_spawn_wall.h"
#include "../../../object_manager/object_manager.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../../components/model_component/model_component.h"
#include "../../../../components/transform_component/transform_component.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../../../game/components/player_component/player_component.h"

const float CSkillSpawnWall::m_cool_time = 15.0f;
const float CSkillSpawnWall::m_duration_time = 5.0f;
const float CSkillSpawnWall::m_wall_spawn_distance = 200.0f;
const float CSkillSpawnWall::m_wall_spawn_height = -100.0f;
const float CSkillSpawnWall::m_effect_scale = 2.0f;

CSkillSpawnWall::CSkillSpawnWall(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
	, m_WallObj(nullptr)
	,m_SkillEffect(nullptr)
{

}

CSkillSpawnWall::~CSkillSpawnWall(void)
{

}

/*!
 *  @brief      初期化
 */
void
CSkillSpawnWall::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

/*!
 *  @brief      更新
 */
void
CSkillSpawnWall::
Update(void)
{
	CSkill::Update();

	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;

	case SKILL_STATE::ACTIVE:
		if (m_WallObj != nullptr)
			CBulletManager::GetInstance().CheckReflectModel(m_WallObj->GetComponent<ModelComponent>()->GetHandle());
		break;

	case SKILL_STATE::COOLDOWN:
		break;
	}
}

/*!
 *  @brief      描画
 */
void
CSkillSpawnWall::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CSkillSpawnWall::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      アクション呼び出し
 */
void
CSkillSpawnWall::
Action(void)
{
	if (m_State != SKILL_STATE::WAIT)
		return;

	CSoundManager::GetInstance().Play_SE(SE_ID::SPAWN_WALL, false);

	CTransform SpawnTr;
	
	//スポーンするオブジェクトの座標
	SpawnTr.position = m_Player.lock()->GetComponent<TransformComponent>()->GetPosition() + m_Player.lock()->GetComponent<PlayerComponent>()->GetForwardVector() * m_wall_spawn_distance;
	SpawnTr.position.y = m_wall_spawn_height;
	//スポーンするオブジェクトの向き
	CVector3 TempVector = m_Player.lock()->GetComponent<PlayerComponent>()->GetForwardVector();
	float TempRotY = asin(TempVector.x) * 180.0f / DX_PI_F;
	if (TempVector.x < 0)
		TempRotY = -TempRotY;
	SpawnTr.rotation = CVector3(0, TempRotY, 0);
	
	m_WallObj = CObjectManager::GetInstance().Create(OBJECT_ID::SKILL_WALL,SpawnTr);
	m_State = SKILL_STATE::ACTIVE;

	m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, CVector3().ZERO, CVector3(), m_effect_scale);
	m_SkillEffect->SetParent(m_Player.lock());
}

/*!
 *  @brief      アクション終了
 */
void
CSkillSpawnWall::
ActionEnd(void)
{
	if (m_SkillEffect != nullptr)
	{
		m_SkillEffect->Delete();
		m_SkillEffect = nullptr;
	}

	if (m_WallObj != nullptr)
	{
		m_WallObj->Delete();
		m_WallObj = nullptr;
	}
}