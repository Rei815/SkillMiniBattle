#pragma once

#include "vivid.h"
#include "..\reward.h"

class CAddBullet : public CReward
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CAddBullet();

    /*!
     *  @brief      デストラクタ
     */
    ~CAddBullet(void);

    /*!
     *  @brief      更新
     */
    void        Update(const vivid::Vector2& position, float offset);

private:

    static const std::string        m_text;

};
