#pragma once

#include "vivid.h"
#include "..\..\..\..\..\utility\utility.h"
#include "..\ui.h"
#include "reward_id.h"
#include "reward/reward.h"
class CWaveRewards : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CWaveRewards();

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CWaveRewards(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(void);

    /*!
     *  @brief      �X�V
     */
    void        Update();

    /*!
     *  @brief      �`��
     */
    void        Draw();

    /*!
     *  @brief      ���
     */
    void        Finalize(void);

protected:

    void        EaseOut(void);
    static const vivid::Vector2     m_position;         //!< �ʒu
    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const float              m_offset;           //!< ��V���m�̋���
    static const float              m_end_time;         //!< �I������
    static const float              m_end_x;           //!< �I���l

    float                           m_StartTime;        //!< �J�n����
    float                           m_StartValue;       //!< �J�n�l
    float                           m_FinishValue;      //!< �I���l
    CEasing                         m_Easing;           //!< �C�[�W���O


    /*!
     *  @brief      REWARD���X�g�^
     */
    using REWARD_LIST = std::vector<CReward*>;

    REWARD_LIST         m_RewardList;               //!< ��V���X�g

    static const int    m_max_reward_num = 3;
    CReward*            m_Rewards[m_max_reward_num];     //!< ��V���X�g����I�΂ꂽ��V

    int                 m_Num;
    int                 m_Nums[m_max_reward_num];
};
