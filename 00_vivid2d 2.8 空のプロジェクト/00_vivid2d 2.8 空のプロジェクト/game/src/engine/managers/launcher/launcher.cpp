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
        std::shared_ptr<CShot> shot = *it;

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

        ++it;
    }

    m_ShotList.clear();
}

CLauncher& CLauncher::GetInstance(void)
{
    static CLauncher instance;

    return instance;
}

std::shared_ptr<CShot> CLauncher::Create(SHOT_ID shotID)
{
    std::shared_ptr<CShot> shot = nullptr;
    switch (shotID)
    {
    case SHOT_ID::BASIC:                 shot = std::make_shared<CBasic>();         break;
    case SHOT_ID::SHOCK_WAVE:            shot = std::make_shared<CShockWave>();     break;
    case SHOT_ID::DODGE_BALL:            shot = std::make_shared<CDodgeBall>();     break;
    case SHOT_ID::MAX:                                                              break;
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
