
/*!
 *  @file       bullet_manager.cpp
 *  @brief      弾管理
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "bullet_manager.h"
#include "..\unit_manager\unit_manager.h"
#include "bullet\normal_bullet\normal_bullet.h"
#include "bullet\homing_bullet\homing_bullet.h"
#include "bullet\shock_wave_bullet\shock_wave_bullet.h"
#include "bullet\cannon_bullet\cannon_bullet.h"
#include "../stage/stage.h"
#include "../effect_manager/effect_manager.h"

 /*
  *  インスタンスの取得
  */
CBulletManager&
CBulletManager::
GetInstance(void)
{
    static CBulletManager instance;

    return instance;
}

/*
 *  初期化
 */
void
CBulletManager::
Initialize(void)
{
    m_BulletList.clear();
}

/*
 *  更新
 */
void
CBulletManager::
Update(void)
{
    // リストが空なら終了
    if (m_BulletList.empty()) return;

    CUnitManager& um = CUnitManager::GetInstance();

    BULLET_LIST::iterator it = m_BulletList.begin();

    while (it != m_BulletList.end())
    {
        IBullet* bullet = (IBullet*)(*it);

        bullet->Update();

        // ユニットマネージャーに弾と当たっているユニットがあるか問い合わせる
        um.CheckHitBullet(bullet);


        // 弾が非アクティブなら削除してリストから外す
        if (!bullet->GetActive())
        {
            bullet->Finalize();

            delete bullet;

            it = m_BulletList.erase(it);

            continue;
        }

        ++it;
    }
}

/*
 *  描画
 */
void
CBulletManager::
Draw(void)
{
    if (m_BulletList.empty()) return;

    BULLET_LIST::iterator it = m_BulletList.begin();

    while (it != m_BulletList.end())
    {
        (*it)->Draw();

        ++it;
    }
}

/*
 *  解放
 */
void
CBulletManager::
Finalize(void)
{
    if (m_BulletList.empty()) return;

    BULLET_LIST::iterator it = m_BulletList.begin();

    while (it != m_BulletList.end())
    {
        (*it)->Finalize();

        delete (*it);

        ++it;
    }

    m_BulletList.clear();
}

std::list<IBullet*> CBulletManager::GetBulletList()
{
    return m_BulletList;
}


/*
 *  弾生成
 */
IBullet*
CBulletManager::
Create(UNIT_CATEGORY category, CShot::BulletParameters* bulletParameter,  CVector3& pos, const CVector3& dir)
{
    IBullet* bullet = nullptr;

    switch (bulletParameter->bulletID)
    {
    case BULLET_ID::NORMAL:         bullet = new CNormalBullet();   break;
    case BULLET_ID::HOMING:         bullet = new CHomingBullet();   break;
    case BULLET_ID::SHOCK_WAVE:     bullet = new CShockWaveBullet();   break;
    case BULLET_ID::CANNON:         bullet = new CCannonBullet();   break;
    }

    if (!bullet) return nullptr;

    bullet->Initialize(category, bulletParameter, pos, dir);

    // 生成した弾をリストに追加
    m_BulletList.push_back(bullet);

    return bullet;
}

void CBulletManager::CheckHitModel(const CModel& model)
{
    // リストが空なら終了
    if (m_BulletList.empty()) return;

    BULLET_LIST::iterator it = m_BulletList.begin();

    while (it != m_BulletList.end())
    {
        IBullet* bullet = (IBullet*)(*it);

        if (!bullet || model.GetModelHandle() == VIVID_DX_ERROR)
            return;

        DxLib::MV1_COLL_RESULT_POLY_DIM hit_poly_dim = MV1CollCheck_Sphere(model.GetModelHandle(), -1, bullet->GetPosition(), bullet->GetRadius());
        if (hit_poly_dim.HitNum >= 1)
        {
            CEffectManager::GetInstance().Create(EFFECT_ID::HIT_INVINCBLE, bullet->GetPosition());
            bullet->SetActive(false);
        }

        // 当たり判定情報の後始末
        MV1CollResultPolyDimTerminate(hit_poly_dim);

        ++it;
    }
}

void CBulletManager::CheckReflectModel(const CModel& model)
{
    // リストが空なら終了
    if (m_BulletList.empty()) return;

    BULLET_LIST::iterator it = m_BulletList.begin();

    while (it != m_BulletList.end())
    {
        IBullet* bullet = (IBullet*)(*it);

        if (!bullet || model.GetModelHandle() == VIVID_DX_ERROR)
            return;

        DxLib::MV1_COLL_RESULT_POLY_DIM hit_poly_dim = MV1CollCheck_Sphere(model.GetModelHandle(), -1, bullet->GetPosition(), bullet->GetRadius());
        if (hit_poly_dim.HitNum >= 1)
        {
            for (int i = 0; i < hit_poly_dim.HitNum; i++)
            {
                CVector3 NowVelocity = -((*it)->GetVelocity());
                CVector3 Normal = hit_poly_dim.Dim[i].Normal;
                float Cos = VDot(NowVelocity, Normal) / (VSize(NowVelocity) * VSize(Normal));
                float Angle = acos(Cos) / DX_PI_F * 180.0f;

                if (Angle >= 90.0f)
                    continue;

                MATRIX Mat = MGetRotVec2(NowVelocity.Normalize(), Normal);

                NowVelocity = VTransform(NowVelocity, Mat);
                NowVelocity = VTransform(NowVelocity, Mat);

                (*it)->SetVelocity(NowVelocity);
                break;
            }
        }

        // 当たり判定情報の後始末
        MV1CollResultPolyDimTerminate(hit_poly_dim);

        ++it;
    }
}

/*
 *  コンストラクタ
 */
CBulletManager::
CBulletManager(void)
{
}

/*
 *  コピーコンストラクタ
 */
CBulletManager::
CBulletManager(const CBulletManager& rhs)
{
    (void)rhs;
}

/*
 *  デストラクタ
 */
CBulletManager::
~CBulletManager(void)
{
}

/*
 *  代入演算子
 */
CBulletManager&
CBulletManager::
operator=(const CBulletManager& rhs)
{
    (void)rhs;

    return *this;
}
