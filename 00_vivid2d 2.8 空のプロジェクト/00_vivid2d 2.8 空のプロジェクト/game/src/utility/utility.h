#pragma once

#include "transform/transform.h"
#include "csv_loader/csv_loader.h"
#include "easing/easing.h"
#include "timer/timer.h"
/*!
 *  @brief      角度をラジアン値に変換
 *
 *  @param[in]  d   角度
 *
 *  @return     ラジアン値
 */
#define DEG_TO_RAD( d )     (float)( (d) * 3.14f / 180.0f )
