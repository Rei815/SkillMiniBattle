
/*!
 *  @file       emergency_effect.h
 *  @brief      �x���G�t�F�N�g
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"
#include "..\effect.h"

 /*!
  *  @class      CEmergencyEffect
  *
  *  @brief      �x���G�t�F�N�g�N���X
  *
  *  @author     Kazuya Maruyama
  *
  *  @date       2020/11/13
  *
  *  @since      1.0
  */
class CEmergencyEffect : public IEffect
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CEmergencyEffect(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CEmergencyEffect(void);

    /*!
     *  @brief      ������
     *
     *  @param[in]  position    �ʒu
     *  @param[in]  color       �F
     *  @param[in]  rotation    ��]�l
     */
    void    Initialize(const vivid::Vector2& position, unsigned int color, float rotation);

    /*!
     *  @brief      �X�V
     */
    void    Update(void);

    /*!
     *  @brief      �`��
     */
    void    Draw(void);

    /*!
     *  @brief      ���
     */
    void    Finalize(void);

private:
    static const int            m_width;                //!< ��
    static const int            m_height;               //!< ����
    static const float          m_fade_speed;           //!< �t�F�[�h���x
    static const int            m_max_velocity;         //!< �ō����x
    static const int            m_max_waring_bar;       //!< �o�[�̌�
    float                       m_AlphaFactor;          //!< �A���t�@�ύX�l
    vivid::Vector2* m_WaringBarPosition;    //!< 
    vivid::Vector2* m_WaringBarVelocity;    //!< 
    int                         m_ActiveTime;
};
