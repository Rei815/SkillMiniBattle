#pragma once

#include "vivid.h"
#include "..\reward.h"

class CDamageUp : public CReward
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CDamageUp();

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CDamageUp(void);

    /*!
     *  @brief      �X�V
     */
    void        Update(const vivid::Vector2& position, float offset);
private:

    
    static const std::string        m_text;

};
