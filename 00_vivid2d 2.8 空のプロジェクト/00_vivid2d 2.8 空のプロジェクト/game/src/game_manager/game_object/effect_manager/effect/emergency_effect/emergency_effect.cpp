
/*!
 *  @file       emergency_effect.cpp
 *  @brief      警告エフェクト
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "emergency_effect.h"
#include "..\..\..\..\..\utility\utility.h"
const int   CEmergencyEffect::m_width = 8;
const int   CEmergencyEffect::m_height = 8;
const float CEmergencyEffect::m_fade_speed = 10.0f;
const int   CEmergencyEffect::m_max_velocity = 11;
const int   CEmergencyEffect::m_max_waring_bar = 4;

/*
 *  コンストラクタ
 */
CEmergencyEffect::
CEmergencyEffect(void)
    : IEffect(m_width, m_height)
    , m_WaringBarPosition(nullptr)
    , m_WaringBarVelocity(nullptr)
{
}

/*
 *  デストラクタ
 */
CEmergencyEffect::
~CEmergencyEffect(void)
{
}

/*
 *  初期化
 */
void
CEmergencyEffect::
Initialize(const vivid::Vector2& position, unsigned int color, float rotation)
{
    IEffect::Initialize(position, color, rotation);

    m_Color = 0xffff0000;

    m_AlphaFactor = 0;

    if (!m_WaringBarPosition)
        m_WaringBarPosition = new vivid::Vector2[m_max_waring_bar];

    m_WaringBarPosition[0].x = 0.0f;
    m_WaringBarPosition[0].y = 250.0f;

    m_WaringBarPosition[1].x = -480.0f;
    m_WaringBarPosition[1].y = 360.0f;

    m_WaringBarPosition[2].x = 960.0f;
    m_WaringBarPosition[2].y = 250.0f;

    m_WaringBarPosition[3].x = 480.0f;
    m_WaringBarPosition[3].y = 360.0f;

    if (!m_WaringBarVelocity)
        m_WaringBarVelocity = new vivid::Vector2[m_max_waring_bar];

    m_WaringBarVelocity[0].x = -1.0f;
    m_WaringBarVelocity[1].x = 1.0f;
    m_WaringBarVelocity[2].x = -1.0f;
    m_WaringBarVelocity[3].x = 1.0f;

    m_ActiveTime = 0;
}

/*
 *  更新
 */
void
CEmergencyEffect::
Update(void)
{
    m_AlphaFactor += DEG_TO_RAD(m_fade_speed);

    int alpha = (m_Color & 0xff000000) >> 24;

    alpha = (int)(abs(cos(m_AlphaFactor)) * 128.0f);

    m_Color = (alpha << 24) | (m_Color & 0x00ffffff);

    for (int i = 0; i < m_max_waring_bar; ++i)
        m_WaringBarPosition[i] += m_WaringBarVelocity[i];

    if (++m_ActiveTime > 120)
    {
        m_ActiveFlag = false;
    }
}

/*
 *  描画
 */
void
CEmergencyEffect::
Draw(void)
{
    for (int i = 0; i < m_max_waring_bar; ++i)
        vivid::DrawTexture("data\\Textures\\warning.png", m_WaringBarPosition[i]);

    //vivid::DrawTexture("data\\Textures\\white.png", m_Position2D, m_Color);

    vivid::DrawTexture("data\\Textures\\emergency.png", vivid::Vector2(vivid::WINDOW_WIDTH / 2.0f - 128.0f, 320.0f - 32.0f), m_Color);
}

/*
 *  解放
 */
void
CEmergencyEffect::
Finalize(void)
{
    if (m_WaringBarPosition)
    {
        delete[] m_WaringBarPosition;

        m_WaringBarPosition = nullptr;
    }

    if (m_WaringBarVelocity)
    {
        delete[] m_WaringBarVelocity;

        m_WaringBarVelocity = nullptr;
    }
}
