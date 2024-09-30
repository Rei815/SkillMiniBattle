#pragma once

#include "vivid.h"
#include "..\reward.h"

class CAddBullet : public CReward
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CAddBullet();

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CAddBullet(void);

    /*!
     *  @brief      �X�V
     */
    void        Update(const vivid::Vector2& position, float offset);

private:

    static const std::string        m_text;

};
