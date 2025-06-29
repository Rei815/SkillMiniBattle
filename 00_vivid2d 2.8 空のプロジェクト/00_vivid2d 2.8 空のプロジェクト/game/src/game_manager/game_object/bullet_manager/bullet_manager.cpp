#include "bullet_manager.h"
#include "..\unit_manager\unit_manager.h"
#include "bullet\shock_wave_bullet\shock_wave_bullet.h"
#include "bullet\cannon_bullet\cannon_bullet.h"
#include "../effect_manager/effect_manager.h"
#include "../sound_manager/sound_manager.h"

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
        std::shared_ptr<IBullet> bullet = *it;

        bullet->Update();

        // ユニットマネージャーに弾と当たっているユニットがあるか問い合わせる
        um.CheckHitBullet(bullet);


        // 弾が非アクティブなら削除してリストから外す
        if (!bullet->IsActive())
        {
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
    m_BulletList.clear();
}

std::list<std::shared_ptr<IBullet>> CBulletManager::GetBulletList()
{
    return m_BulletList;
}


/*
 *  弾生成
 */
std::shared_ptr<IBullet>
CBulletManager::
Create(UNIT_CATEGORY category, CShot::BulletParameters* bulletParameter,  CVector3& pos, const CVector3& dir)
{
    std::shared_ptr<IBullet> bullet = nullptr;

    switch (bulletParameter->bulletID)
    {
    case BULLET_ID::SHOCK_WAVE:     bullet = std::make_shared<CShockWaveBullet>();   break;
    case BULLET_ID::CANNON:         bullet = std::make_shared<CCannonBullet>();   break;
    }

    if (!bullet) return nullptr;

    bullet->Initialize(category, bulletParameter, pos, dir);

    // 生成した弾をリストに追加
    m_BulletList.emplace_back(bullet);

    return bullet;
}

/*
 *  弾生成
 */
std::shared_ptr<IBullet> CBulletManager::Create(UNIT_CATEGORY category, BULLET_ID id, CVector3& pos, const CVector3& dir)
{
    std::shared_ptr<IBullet> bullet = nullptr;

    switch (id)
    {
    case BULLET_ID::SHOCK_WAVE:     bullet = std::make_shared<CShockWaveBullet>();  break;
    case BULLET_ID::CANNON:         bullet = std::make_shared<CCannonBullet>();     break;
    }

    if (!bullet) return nullptr;

    bullet->Initialize(category, pos, dir);

    // 生成した弾をリストに追加
    m_BulletList.emplace_back(bullet);

    return bullet;
}

void CBulletManager::CheckReflectModel(const CModel& model)
{
    // リストが空なら終了
    if (m_BulletList.empty()) return;

    BULLET_LIST::iterator it = m_BulletList.begin();

    while (it != m_BulletList.end())
    {
        std::shared_ptr<IBullet> bullet = *it;

        if (!bullet || model.GetHandle() == VIVID_DX_ERROR)
        {
            ++it;
            continue;
        }

        DxLib::MV1_COLL_RESULT_POLY_DIM hit_poly_dim = MV1CollCheck_Sphere(model.GetHandle(), -1, bullet->GetPosition(), bullet->GetRadius());
        if (hit_poly_dim.HitNum >= 1)
        {
            CSoundManager::GetInstance().Play_SE(SE_ID::REFLECTION, false);

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
