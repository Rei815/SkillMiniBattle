
/*!
 *  @file       easing.h
 *  @brief      イージング関数
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "..\..\mathematics\mathematics.h"

namespace Easing
{

    /*!
        *  @brief  線形補間
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    float Linear(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    float InQuad(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    float OutQuad(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    float InOutQuad(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    static float InCubic(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    static float OutCubic(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    static float InOutCubic(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    static float InQuart(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    float OutQuart(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    static float InOutQuart(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    static float InQuintic(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    static float OutQuintic(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    static float InOutQuintic(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    float InSine(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    static float OutSine(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time   終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    static float InOutSine(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    static float InExp(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time   終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    static float OutExp(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    static float InOutExp(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    static float InCirc(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    static float OutCirc(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    static float InOutCirc(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    static float OutBounce(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    static float InBounce(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        */
    static float InOutBounce(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        *  @param[in]  s           係数
        */
    static float OutBack(float time, float finish_time, float min = 0.0f, float max = 1.0f, float s = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        *  @param[in]  s           係数
        */
    static float InBack(float time, float finish_time, float min = 0.0f, float max = 1.0f, float s = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        経過時間
        *  @param[in]  finish_time 終了時間
        *  @param[in]  min         最小値
        *  @param[in]  max         最大値
        *  @param[in]  s           係数
        */
    static float InOutBack(float time, float finish_time, float min = 0.0f, float max = 1.0f, float s = 1.0f);

};
