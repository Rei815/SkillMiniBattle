#pragma once

#include "vivid.h"
#include "..\reward.h"

class CAddShot : public CReward
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CAddShot();

    /*!
     *  @brief      デストラクタ
     */
    ~CAddShot(void);

    /*!
     *  @brief      更新
     */
    void        Update(const vivid::Vector2& position, float offset);

private:

    static const std::string        m_text;

};
