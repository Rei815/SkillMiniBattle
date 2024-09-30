#include "wave_rewards.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../ui_manager.h"
#include "reward/add_life/add_life.h"
#include "reward/add_shot/add_shot.h"
#include "reward/add_bullet/add_bullet.h"
#include "reward/damage_up/damage_up.h"
const int               CWaveRewards::m_height = 512;
const int               CWaveRewards::m_width = 1024;
const vivid::Vector2    CWaveRewards::m_position = vivid::Vector2((float)vivid::WINDOW_WIDTH + (float)m_width / 2.0f, (float)vivid::WINDOW_HEIGHT / 2.0f - (float)m_height / 2.0f);
const float             CWaveRewards::m_end_time = 0.5f;
const float             CWaveRewards::m_end_x = (float)vivid::WINDOW_WIDTH / 2.0f - (float)m_width / 2.0f;
const float             CWaveRewards::m_offset = 300;

/*
 *  コンストラクタ
 */
CWaveRewards::
CWaveRewards()
    : CUI(m_width, m_height)
    , m_Easing(CEasing())
    , m_StartTime(0.0f)
    , m_FinishValue(0.0f)
    , m_Num(-1)
{
    std::fill_n(m_Nums, m_max_reward_num, -1);

}

/*
 *  デストラクタ
 */
CWaveRewards::
~CWaveRewards(void)
{
}

/*
 *  初期化
 */
void
CWaveRewards::
Initialize(void)
{
    m_Position = m_position;
    m_StartValue = m_position.x;
    m_StartTime = 0.0f;
    m_FinishValue = m_end_x;
    m_Easing.easingState = CEasing::EASING_STATE::EASE_OUT;
    m_Attributes.push_back(UI_ATTRIBUTE::WAVE_REWARD);
    m_UI_ID = UI_ID::WAVE_REWARD;
    m_RewardList.push_back(new CAddLife());
    m_RewardList.push_back(new CAddShot());
    m_RewardList.push_back(new CAddBullet());
    m_RewardList.push_back(new CDamageUp());
    for (int i = 0; i < m_max_reward_num; i++)
    {

        bool flag = false;
        while (flag == false)
        {
            m_Num = rand() % m_RewardList.capacity();
            for (int i = 0; i < m_max_reward_num; i++)
            {
                if (m_Num == m_Nums[i])
                    break;

        
                if (m_Nums[i] == -1)
                {
                    m_Nums[i] = m_Num;
                    flag = true;
                    break;
                }
            }
        }


        m_Rewards[i] = m_RewardList.at(m_Num);
        m_Rewards[i]->Initialize(m_Position);
    }
}

/*
 *  更新
 */
void
CWaveRewards::
Update()
{
    EaseOut();
    for (int i = 0; i < m_max_reward_num; i++)
    {
        m_Rewards[i]->Update(vivid::Vector2(m_Position.x + m_width / 2.0f, m_Position.y + (float)m_height / 6.0f), m_offset * (i - 1));
    }

    if (CUIManager::GetInstance().GetReceivedReward())
    {
        m_ActiveFlag = false;
    }
}
/*
 *  描画
 */
void
CWaveRewards::
Draw()
{
    vivid::DrawTexture("data\\Textures\\wave_rewards_background.png", m_Position);
    for (int i = 0; i < m_max_reward_num; i++)
    {
        m_Rewards[i]->Draw();
    }

}

/*
 *  解放
 */
void
CWaveRewards::Finalize(void)
{
    for (int i = 0; i < m_max_reward_num; i++)
    {
        m_Rewards[i]->Finalize();
    }

}


void CWaveRewards::EaseOut(void)
{
    if (m_Position.x != m_end_x)
    {
        float current_x = m_Easing.OutQuart(m_StartTime, m_end_time, m_StartValue, m_FinishValue);

        m_Position.x = current_x;

        m_StartTime += vivid::GetDeltaTime();
    }
    else
    {
        m_Position.x = m_end_x;
    }

}