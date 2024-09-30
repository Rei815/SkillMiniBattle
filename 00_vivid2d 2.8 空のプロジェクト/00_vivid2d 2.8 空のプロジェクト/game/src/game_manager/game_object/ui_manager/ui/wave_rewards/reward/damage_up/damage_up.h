#pragma once

#include "vivid.h"
#include "..\reward.h"

class CDamageUp : public CReward
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CDamageUp();

    /*!
     *  @brief      デストラクタ
     */
    ~CDamageUp(void);

    /*!
     *  @brief      更新
     */
    void        Update(const vivid::Vector2& position, float offset);
private:

    
    static const std::string        m_text;

};
