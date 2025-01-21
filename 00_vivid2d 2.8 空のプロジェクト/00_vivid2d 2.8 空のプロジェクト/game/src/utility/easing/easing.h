
/*!
 *  @file       easing.h
 *  @brief      �C�[�W���O�֐�
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
        *  @brief  ���`���
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    float Linear(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    float InQuad(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    float OutQuad(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    float InOutQuad(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    static float InCubic(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    static float OutCubic(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    static float InOutCubic(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    static float InQuart(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    float OutQuart(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    static float InOutQuart(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    static float InQuintic(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    static float OutQuintic(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    static float InOutQuintic(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    float InSine(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    static float OutSine(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time   �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    static float InOutSine(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    static float InExp(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time   �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    static float OutExp(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    static float InOutExp(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    static float InCirc(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    static float OutCirc(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    static float InOutCirc(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    static float OutBounce(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    static float InBounce(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        */
    static float InOutBounce(float time, float finish_time, float min = 0.0f, float max = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        *  @param[in]  s           �W��
        */
    static float OutBack(float time, float finish_time, float min = 0.0f, float max = 1.0f, float s = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        *  @param[in]  s           �W��
        */
    static float InBack(float time, float finish_time, float min = 0.0f, float max = 1.0f, float s = 1.0f);

    /*!
        *  @brief
        *
        *  @param[in]  time        �o�ߎ���
        *  @param[in]  finish_time �I������
        *  @param[in]  min         �ŏ��l
        *  @param[in]  max         �ő�l
        *  @param[in]  s           �W��
        */
    static float InOutBack(float time, float finish_time, float min = 0.0f, float max = 1.0f, float s = 1.0f);

};
