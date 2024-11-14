#pragma once

#include "transform/transform.h"
#include "csv_loader/csv_loader.h"
#include "easing/easing.h"
#include "timer/timer.h"
/*!
 *  @brief      �p�x�����W�A���l�ɕϊ�
 *
 *  @param[in]  d   �p�x
 *
 *  @return     ���W�A���l
 */
#define DEG_TO_RAD( d )     (float)( (d) * 3.14f / 180.0f )

#define REVOLVE_RATE	DX_TWO_PI_F / 360.0f;