
/*!
*  @file       easing.cpp
*  @brief      イージング関数
*  @author     Kazuya Maruyama
*  @date       2021/03/10
*  @version    7.17
*
*  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
*/

#include "easing.h"
#include <cmath>
#include "../utility.h"
#define _USE_MATH_DEFINES
#include <math.h>

CEasing::CEasing()
    : easingState(EASING_STATE::EASE_IN)
{
}
CEasing::~CEasing()
{
}
/*
 *
 */
float
CEasing::
Linear(float time, float finish_time, float min, float max)
{
    return (max - min) * time / finish_time + min;
}

/*
 *
 */
float
CEasing::
InQuad(float time, float finish_time, float min, float max)
{
    max -= min;

    time /= finish_time;

    return max * time * time + min;
}

/*
 *
 */
float
CEasing::
OutQuad(float time, float finish_time, float min, float max)
{
    max -= min;

    time /= finish_time;

    return -max * time * (time - 2.0f) + min;
}

/*
 *
 */
float
CEasing::
InOutQuad(float time, float finish_time, float min, float max)
{
    max -= min;

    time /= finish_time / 2.0f;

    if (time < 1.0f)
        return max / 2.0f * time * time + min;

    time -= 1.0f;

    return -max / 2.0f * (time * (time - 2.0f) - 1.0f) + min;
}

/*
 *
 */
float
CEasing::
InCubic(float time, float finish_time, float min, float max)
{
    max -= min;

    time /= finish_time;

    return max * time * time * time + min;
}

/*
 *
 */
float
CEasing::
OutCubic(float time, float finish_time, float min, float max)
{
    max -= min;

    time = time / finish_time - 1.0f;

    return max * (time * time * time + 1.0f) + min;
}

/*
 *
 */
float
CEasing::
InOutCubic(float time, float finish_time, float min, float max)
{
    max -= min;

    time /= finish_time / 2.0f;

    if (time < 1.0f)

        return max / 2.0f * time * time * time + min;

    time -= 2.0f;

    return max / 2.0f * (time * time * time + 2.0f) + min;
}

/*
 *
 */
float
CEasing::
InQuart(float time, float finish_time, float min, float max)
{
    max -= min;

    time /= finish_time;

    return max * time * time * time * time + min;
}

/*
 *
 */
float
CEasing::
OutQuart(float time, float finish_time, float min, float max)
{
    max -= min;

    time = time / finish_time - 1.0f;

    return -max * (time * time * time * time - 1.0f) + min;
}

/*
 *
 */
float
CEasing::
InOutQuart(float time, float finish_time, float min, float max)
{
    max -= min;

    time /= finish_time / 2.0f;

    if (time < 1.0f)
        return max / 2.0f * time * time * time * time + min;

    time -= 2.0f;

    return -max / 2.0f * (time * time * time * time - 2.0f) + min;
}

/*
 *
 */
float
CEasing::
InQuintic(float time, float finish_time, float min, float max)
{
    max -= min;

    time /= finish_time;

    return max * time * time * time * time * time + min;
}

/*
 *
 */
float
CEasing::
OutQuintic(float time, float finish_time, float min, float max)
{
    max -= min;

    time = time / finish_time - 1.0f;

    return max * (time * time * time * time * time + 1.0f) + min;
}

/*
 *
 */
float
CEasing::
InOutQuintic(float time, float finish_time, float min, float max)
{
    max -= min;

    time /= finish_time / 2.0f;

    if (time < 1.0f)
        return max / 2.0f * time * time * time * time * time + min;

    time -= 2.0f;

    return max / 2.0f * (time * time * time * time * time + 2.0f) + min;
}

/*
 *
 */
float
CEasing::
InSine(float time, float finish_time, float min, float max)
{
    max -= min;

    return -max * cosf(time * DEG_TO_RAD(90.0f) / finish_time) + max + min;
}

/*
 *
 */
float
CEasing::
OutSine(float time, float finish_time, float min, float max)
{
    max -= min;

    return max * sinf(time * DEG_TO_RAD(90.0f) / finish_time) + min;
}

/*
 *
 */
float
CEasing::
InOutSine(float time, float finish_time, float min, float max)
{
    max -= min;

    return -max / 2.0f * (cosf(time * M_PI / finish_time) - 1.0f) + min;
}

/*
 *
 */
float
CEasing::
InExp(float time, float finish_time, float min, float max)
{
    max -= min;

    return time == 0.0f ? min : max * powf(2.0f, 10.0f * (time / finish_time - 1.0f)) + min;
}

/*
 *
 */
float
CEasing::
OutExp(float time, float finish_time, float min, float max)
{
    max -= min;

    return time == finish_time ? max + min : max * (-powf(2.0f, -10.0f * time / finish_time) + 1) + min;
}

/*
 *
 */
float
CEasing::
InOutExp(float time, float finish_time, float min, float max)
{
    if (time == 0.0f) return min;

    if (time == finish_time) return max;

    max -= min;

    time /= finish_time / 2.0f;

    if (time < 1.0f)
        return max / 2.0f * powf(2.0f, 10.0f * (time - 1.0f)) + min;

    time -= 1.0f;

    return max / 2.0f * (-powf(2.0f, -10.0f * time) + 2.0f) + min;
}

/*
 *
 */
float
CEasing::
InCirc(float time, float finish_time, float min, float max)
{
    max -= min;

    time /= finish_time;

    return -max * (sqrtf(1.0f - time * time) - 1.0f) + min;
}

/*
 *
 */
float
CEasing::
OutCirc(float time, float finish_time, float min, float max)
{
    max -= min;

    time = time / finish_time - 1.0f;

    return max * sqrtf(1.0f - time * time) + min;
}

/*
 *
 */
float
CEasing::
InOutCirc(float time, float finish_time, float min, float max)
{
    max -= min;

    time /= finish_time / 2.0f;

    if (time < 1.0f)
        return -max / 2.0f * (sqrtf(1.0f - time * time) - 1.0f) + min;

    time -= 2.0f;

    return max / 2.0f * (sqrtf(1.0f - time * time) + 1.0f) + min;
}

/*
 *
 */
float
CEasing::
OutBounce(float time, float finish_time, float min, float max)
{
    max -= min;

    time /= finish_time;

    if (time < 1.0f / 2.75f)
    {
        return max * (7.5625f * time * time) + min;
    }
    else if (time < 2.0f / 2.75f)
    {
        time -= 1.5f / 2.75f;

        return max * (7.5625f * time * time + 0.75f) + min;
    }
    else if (time < 2.5f / 2.75f)
    {
        time -= 2.25f / 2.75f;

        return max * (7.5625f * time * time + 0.9375f) + min;
    }
    else
    {
        time -= 2.625f / 2.75f;

        return max * (7.5625f * time * time + 0.984375f) + min;
    }
}

/*
 *
 */
float
CEasing::
InBounce(float time, float finish_time, float min, float max)
{
    max -= min;

    time /= finish_time;

    return max * pow(2.0f, 6.0f * (time - 1.0f)) * abs(sin(time * M_PI * 3.5f)) + min;

    //return max - OutBounce(finish_time - time, finish_time, 0.0f, max - min) + min;
}

/*
 *
 */
float
CEasing::
InOutBounce(float time, float finish_time, float min, float max)
{
    max -= min;

    time /= finish_time;

    if (time < 0.5f)
        return max * 8.0f * pow(2.0f, 8.0f * (time - 1.0f)) * abs(sin(time * M_PI * 7.0f)) + min;
    else
        return max * (1.0f - 8.0f * pow(2.0f, -8.0f * time) * abs(sin(time * M_PI * 7.0f))) + min;

    //if (time < finish_time / 2.0f)
    //    return InBounce(time * 2.0f, finish_time, min, max) * 0.5f + min;
    //else
    //    return OutBounce(time * 2.0f - finish_time, finish_time, 0.0f, max ) * 0.5f + (max - min) * 0.5f;
}

/*
 *
 */
float
CEasing::
OutBack(float time, float finish_time, float min, float max, float s)
{
    max -= min;

    time = time / finish_time - 1.0f;

    return max * (time * time * ((s + 1.0f) * time + s) + 1.0f) + min;
}

/*
 *
 */
float
CEasing::
InBack(float time, float finish_time, float min, float max, float s)
{
    max -= min;

    time /= finish_time;

    return max * time * time * ((s + 1.0f) * time - s) + min;
}

/*
 *
 */
float
CEasing::
InOutBack(float time, float finish_time, float min, float max, float s)
{
    max -= min;

    s *= 1.525f;

    time /= finish_time / 2.0f;

    if (time < 1.0f)
        return max / 2.0f * (time * time * ((s + 1.0f) * time - s)) + min;

    time -= 2;

    return max / 2.0f * (time * time * ((s + 1.0f) * time + s) + 2.0f) + min;
}
