#pragma once

#include "vivid.h"
#include "..\reward.h"

class CAddShot : public CReward
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CAddShot();

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CAddShot(void);

    /*!
     *  @brief      �X�V
     */
    void        Update(const vivid::Vector2& position, float offset);

private:

    static const std::string        m_text;

};
