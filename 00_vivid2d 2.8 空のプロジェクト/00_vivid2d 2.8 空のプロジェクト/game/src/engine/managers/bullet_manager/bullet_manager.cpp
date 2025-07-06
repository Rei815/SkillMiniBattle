#include "bullet_manager.h"
#include "bullet\shock_wave_bullet\shock_wave_bullet.h"
#include "bullet\cannon_bullet\cannon_bullet.h"
#include "../effect_manager/effect_manager.h"
#include "../sound_manager/sound_manager.h"
#include "../object_manager/object_manager.h"

 /*
  *  �C���X�^���X�̎擾
  */
CBulletManager&
CBulletManager::
GetInstance(void)
{
    static CBulletManager instance;

    return instance;
}

/*
 *  ������
 */
void
CBulletManager::
Initialize(void)
{
    m_BulletList.clear();
}

/*
 *  �X�V
 */
void
CBulletManager::
Update(void)
{
    // ���X�g����Ȃ�I��
    if (m_BulletList.empty()) return;

    CObjectManager& um = CObjectManager::GetInstance();

    BULLET_LIST::iterator it = m_BulletList.begin();

    while (it != m_BulletList.end())
    {
        std::shared_ptr<IBullet> bullet = *it;

        bullet->Update();

        // ���j�b�g�}�l�[�W���[�ɒe�Ɠ������Ă��郆�j�b�g�����邩�₢���킹��
        um.CheckHitBullet(bullet);


        // �e����A�N�e�B�u�Ȃ�폜���ă��X�g����O��
        if (!bullet->IsActive())
        {
            it = m_BulletList.erase(it);

            continue;
        }

        ++it;
    }
}

/*
 *  �`��
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
 *  ���
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
 *  �e����
 */
std::shared_ptr<IBullet>
CBulletManager::
Create(FACTION_CATEGORY category, CShot::BulletParameters* bulletParameter,  CVector3& pos, const CVector3& dir)
{
    std::shared_ptr<IBullet> bullet = nullptr;

    switch (bulletParameter->bulletID)
    {
    case BULLET_ID::SHOCK_WAVE:     bullet = std::make_shared<CShockWaveBullet>();   break;
    case BULLET_ID::CANNON:         bullet = std::make_shared<CCannonBullet>();   break;
    }

    if (!bullet) return nullptr;

    bullet->Initialize(category, bulletParameter, pos, dir);

    // ���������e�����X�g�ɒǉ�
    m_BulletList.emplace_back(bullet);

    return bullet;
}

/*
 *  �e����
 */
std::shared_ptr<IBullet> CBulletManager::Create(FACTION_CATEGORY category, BULLET_ID id, CVector3& pos, const CVector3& dir)
{
    std::shared_ptr<IBullet> bullet = nullptr;

    switch (id)
    {
    case BULLET_ID::SHOCK_WAVE:     bullet = std::make_shared<CShockWaveBullet>();  break;
    case BULLET_ID::CANNON:         bullet = std::make_shared<CCannonBullet>();     break;
    }

    if (!bullet) return nullptr;

    bullet->Initialize(category, pos, dir);

    // ���������e�����X�g�ɒǉ�
    m_BulletList.emplace_back(bullet);

    return bullet;
}

void CBulletManager::CheckReflectModel(int model_handle)
{
    // ���X�g����Ȃ�I��
    if (m_BulletList.empty()) return;

    BULLET_LIST::iterator it = m_BulletList.begin();

    while (it != m_BulletList.end())
    {
        std::shared_ptr<IBullet> bullet = *it;

        if (!bullet || model_handle == VIVID_DX_ERROR)
        {
            ++it;
            continue;
        }

        DxLib::MV1_COLL_RESULT_POLY_DIM hit_poly_dim = MV1CollCheck_Sphere(model_handle, -1, bullet->GetPosition(), bullet->GetRadius());
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

        // �����蔻����̌�n��
        MV1CollResultPolyDimTerminate(hit_poly_dim);

        ++it;
    }
}

/*
 *  �R���X�g���N�^
 */
CBulletManager::
CBulletManager(void)
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
CBulletManager::
CBulletManager(const CBulletManager& rhs)
{
    (void)rhs;
}

/*
 *  �f�X�g���N�^
 */
CBulletManager::
~CBulletManager(void)
{
}

/*
 *  ������Z�q
 */
CBulletManager&
CBulletManager::
operator=(const CBulletManager& rhs)
{
    (void)rhs;

    return *this;
}
