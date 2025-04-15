#include "launcher.h"
#include "../bullet_manager/bullet_manager.h"
#include "shot/basic/basic.h"
#include "shot/shock_wave/shock_wave.h"
#include "shot/dodge_ball/dodge_ball.h"

/*
 *  ������
 */
void CLauncher::Initialize(void)
{
    m_ShotList.clear();
}

/*
 *  �X�V
 */
void CLauncher::Update(void)
{
    if (m_ShotList.empty()) return;

    SHOT_LIST::iterator it = m_ShotList.begin();

    while (it != m_ShotList.end())
    {
        CShot* shot = (CShot*)(*it);

        shot->Update();

        ++it;
    }
}

/*
 *  ���
 */
void CLauncher::Finalize(void)
{
    if (m_ShotList.empty()) return;

    SHOT_LIST::iterator it = m_ShotList.begin();

    while (it != m_ShotList.end())
    {
        (*it)->Finalize();

        delete (*it);

        ++it;
    }

    m_ShotList.clear();
}

CLauncher& CLauncher::GetInstance(void)
{
    static CLauncher instance;

    return instance;
}

CShot* CLauncher::Create(SHOT_ID shotID)
{
    CShot* shot = nullptr;
    switch (shotID)
    {
    case SHOT_ID::BASIC:                 shot = new CBasic();               break;
    case SHOT_ID::SHOCK_WAVE:            shot = new CShockWave();           break;
    case SHOT_ID::DODGE_BALL:            shot = new CDodgeBall();           break;
    case SHOT_ID::MAX:                                                      break;
    }

    if (!shot)
        return nullptr;
    shot->Initialize();
    m_ShotList.push_back(shot);

    return shot;
}

/*
 *  �R���X�g���N�^
 */
CLauncher::
CLauncher(void)
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
CLauncher::
CLauncher(const CLauncher& rhs)
{
    (void)rhs;
}

/*
 *  �f�X�g���N�^
 */
CLauncher::
~CLauncher(void)
{
}

/*
 *  ������Z�q
 */
CLauncher&
CLauncher::
operator=(const CLauncher& rhs)
{
    (void)rhs;

    return *this;
}
