
/*!
 *  @file       unit.cpp
 *  @brief      ���j�b�g
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "unit.h"
#include "..\..\..\..\utility\utility.h"
#include "..\..\effect_manager\effect_manager.h"
#include "..\..\sound_manager\sound_manager.h"
#include "..\..\camera\camera.h"
#include "../../bullet_manager/bullet/bullet.h"
#include <vivid.cpp>
#include "../unit_manager.h"

const float             IUnit::m_destroy_scale_adjust = 25.0f;
const float             IUnit::m_alpha_speed = 0.025f;
const CVector3          IUnit::m_gravity = CVector3(0.0f, -1.0f, 0.0f);

IUnit::IUnit()
{
}

/*
 *  �R���X�g���N�^
 */
IUnit::
IUnit(UNIT_CATEGORY category, UNIT_ID unit_id)
    : m_Transform(CTransform())
    , m_Velocity(CVector3())
    , m_ActiveFlag(true)
    , m_Category(category)
    , m_UnitID(unit_id)
    , m_InvincibleFlag(false)
    , m_UnitState(UNIT_STATE::ATTACK)
    , m_Max_Vertex()
    , m_Radius()
    , m_DamageRate(1.0f)
    , m_Shot()
    , m_Alpha()
    , m_DefeatFlag(false)
    , m_Gravity()
{
}

/*
 *  �f�X�g���N�^
 */
IUnit::
~IUnit(void)
{
}

/*
 *  ������
 */
void
IUnit::
Initialize(UNIT_ID id, const CVector3& position, const std::string& file_name, vivid::controller::DEVICE_ID controller)
{
    m_UnitID = id;
    m_Transform.position = position;
    m_Velocity = CVector3();
    m_ActiveFlag = true;
    m_InvincibleFlag = false;
    m_UnitState = UNIT_STATE::APPEAR;
    m_Alpha = 0.0f;
    m_RevertAlpha = false;
    m_DecAlpha = false;
    m_FileName = file_name;
    m_Gravity = m_gravity;
}
/*
 *  �X�V
 */
void
IUnit::
Update(void)
{
    m_Velocity += m_Gravity;

    switch (m_UnitState)
    {
    case UNIT_STATE::APPEAR:    Appear();      break;
    case UNIT_STATE::ATTACK:    Attack();      break;
    case UNIT_STATE::DEFEAT:    Defeat();      break;
    }
}

/*
 *  �`��
 */
void
IUnit::
Draw(void)
{
}

/*
 *  ���
 */
void
IUnit::
Finalize(void)
{
}

/*
 *  �A�^������`�F�b�N
 */
bool
IUnit::
CheckHitBullet(IBullet* bullet)
{
    if (!bullet || m_Category == bullet->GetBulletCategory() || m_UnitState == UNIT_STATE::DEFEAT)
        return false;
    DxLib::MV1_COLL_RESULT_POLY_DIM hit_poly_dim{};
    switch (bullet->GetColliderID())
    {
    case COLLIDER_ID::SPHERE:
        hit_poly_dim = MV1CollCheck_Sphere(m_Model.GetModelHandle(), -1, bullet->GetPosition(), bullet->GetRadius());
        break;
    case COLLIDER_ID::CAPSULE:
        hit_poly_dim = MV1CollCheck_Capsule(m_Model.GetModelHandle(), -1, bullet->GetColliderPosA(), bullet->GetColliderPosB(),bullet->GetRadius());
        break;
    }
    bool hit_flag = false;

    if (hit_poly_dim.HitNum >= 1)
    {
        hit_flag = true;
        CVector3 hitPosition;
        hitPosition.x = hit_poly_dim.Dim->HitPosition.x;
        hitPosition.y = hit_poly_dim.Dim->HitPosition.y;
        hitPosition.z = hit_poly_dim.Dim->HitPosition.z;
        if (m_InvincibleFlag)
            CEffectManager::GetInstance().Create(EFFECT_ID::HIT_INVINCBLE, hitPosition);
        else
            CEffectManager::GetInstance().Create(EFFECT_ID::HIT, hitPosition);

        bullet->SetActive(false);

        if (m_InvincibleFlag)
            return hit_flag;

        HitBullet(bullet, hitPosition);
    }
    // �����蔻����̌�n��
    MV1CollResultPolyDimTerminate(hit_poly_dim);
    return hit_flag;
}


/*
 *  ���j�b�gID�擾
 */
UNIT_ID
IUnit::
GetUnitID(void)
{
    return m_UnitID;
}

/*
 *  �ʒu�擾
 */
CVector3
IUnit::
GetPosition(void)
{
    return m_Transform.position;
}

/*
 *  �ʒu�ݒ�
 */
void
IUnit::
SetPosition(const CVector3& positioin)
{
    m_Transform.position = positioin;
}

/*
 *  �A�N�e�B�u�t���O�擾
 */
bool
IUnit::
GetActive(void)
{
    return m_ActiveFlag;
}

/*
 *  �A�N�e�B�u�t���O�ݒ�
 */
void
IUnit::
SetActive(bool active)
{
    m_ActiveFlag = active;
}

/*
 *  ���j�b�g���ʎq�擾
 */
UNIT_CATEGORY
IUnit::
GetUnitCategory(void)
{
    return m_Category;
}

/*
 *  ���G�t���O�擾
 */
bool
IUnit::
GetInvincibleFlag(void)
{
    return m_InvincibleFlag;
}

/*
 *  ���G�t���O�ݒ�
 */
void
IUnit::
SetInvincibleFlag(bool flag)
{
    m_InvincibleFlag = flag;
}

/*
 *  ���j�b�g��Ԏ擾
 */
UNIT_STATE
IUnit::
GetUnitState(void)
{
    return m_UnitState;
}

/*
 *  ���j�b�g��Ԑݒ�
 */
void
IUnit::
SetUnitState(UNIT_STATE state)
{
    m_UnitState = state;
}

CVector3 IUnit::GetVelocity()
{
    return m_Velocity;
}

void IUnit::SetVelocity(const CVector3& velocity)
{
    m_Velocity = velocity;
}

float IUnit::GetRadius(void)
{
    return m_Radius;
}

float IUnit::GetHeight(void)
{
    return m_Height;
}

void IUnit::AddShot(void)
{
    m_Shot->AddShot();
}

void IUnit::AddBullet(void)
{
    m_Shot->AddBullet();
}

void IUnit::DamageUp(float damageRate)
{
    m_DamageRate += damageRate;
}

float IUnit::GetDamageRate(void)
{
    return m_DamageRate;
}

bool IUnit::GetDefeatFlag(void)
{
    return m_DefeatFlag;
}

void IUnit::SetDefeatFlag(bool flag)
{
    m_DefeatFlag = flag;
}

CModel IUnit::GetModel(void)
{
    return m_Model;
}

void IUnit::SetIsGround(bool flag)
{
    m_IsGround = flag;
}

void IUnit::SetGravity(const CVector3& gravity)
{
    m_Gravity = gravity;
}

void IUnit::RevertAlpha(void)
{
    if (m_Alpha >= 1.0f)
        m_Alpha = 1.0f;

    //�A���t�@�l�����ɖ߂�����I��
    if (m_Alpha == 1.0f) { m_RevertAlpha = false; return; }

    m_Alpha += m_alpha_speed;

    MV1SetOpacityRate(m_Model.GetModelHandle(), m_Alpha);
}

void IUnit::DecAlpha(void)
{
    if (m_Alpha <= 0.0f)
        m_Alpha = 0.0f;

    //�A���t�@�l��0�ɂȂ�����I��
    if (m_Alpha == 0.0f) { m_DecAlpha = false; return; }

    m_Alpha -= m_alpha_speed;

    MV1SetOpacityRate(m_Model.GetModelHandle(), m_Alpha);

}

void IUnit::Appear(void)
{
    if (m_Alpha == 1.0f)
        m_UnitState = UNIT_STATE::ATTACK;

    RevertAlpha();
}

/*
 *  �U��
 */
void
IUnit::
Attack(void)
{
}

void IUnit::Fire(CShot* shot, bool aim, CVector3& position)
{
    IUnit* player = nullptr;
    CVector3 dir = CVector3::BACK;
    if (!shot)
        return;
    if (aim)
    {
        player = CUnitManager::GetInstance().GetPlayer(UNIT_ID::PLAYER1);
    }
    if (player)
    {
        dir = player->GetPosition() - position;

        dir = dir.Normalize();

    }
    shot->Shot(m_Category, position, dir);

}

void IUnit::Fire(CShot* shot, bool aim, CVector3& position, const CVector3& direction)
{
    IUnit* player = nullptr;
    CVector3 dir = direction;
    if (!shot)
        return;
    if (aim)
    {
        player = CUnitManager::GetInstance().GetPlayer(UNIT_ID::PLAYER1);
    }
    if (player)
    {
        dir = player->GetPosition() - position;

        dir = dir.Normalize();

    }
    shot->Shot(m_Category, position, dir);

}

void IUnit::HitBullet(IBullet* bullet, CVector3 hit_position)
{
    //�p����ŏ��������
}


/*
 *  ���S
 */
void
IUnit::
Defeat(void)
{
    m_DefeatFlag = true;
}

void IUnit::Delete(void)
{
    m_ActiveFlag = false;

}
