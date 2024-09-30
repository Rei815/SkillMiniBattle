
/*!
 *  @file       emergency_effect.h
 *  @brief      警告エフェクト
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
  *  @brief      警告エフェクトクラス
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
     *  @brief      コンストラクタ
     */
    CEmergencyEffect(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CEmergencyEffect(void);

    /*!
     *  @brief      初期化
     *
     *  @param[in]  position    位置
     *  @param[in]  color       色
     *  @param[in]  rotation    回転値
     */
    void    Initialize(const vivid::Vector2& position, unsigned int color, float rotation);

    /*!
     *  @brief      更新
     */
    void    Update(void);

    /*!
     *  @brief      描画
     */
    void    Draw(void);

    /*!
     *  @brief      解放
     */
    void    Finalize(void);

private:
    static const int            m_width;                //!< 幅
    static const int            m_height;               //!< 高さ
    static const float          m_fade_speed;           //!< フェード速度
    static const int            m_max_velocity;         //!< 最高速度
    static const int            m_max_waring_bar;       //!< バーの個数
    float                       m_AlphaFactor;          //!< アルファ変更値
    vivid::Vector2* m_WaringBarPosition;    //!< 
    vivid::Vector2* m_WaringBarVelocity;    //!< 
    int                         m_ActiveTime;
};
