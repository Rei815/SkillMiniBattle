#pragma once

 /*!
  *  @brief      エフェクトID
  */
enum class EFFECT_ID
{
    HIT,                    //!< ヒットエフェクト
    JUMP,                   //!< ジャンプエフェクト
    DUST_CLOUD,             //!< 土煙エフェクト
    SHOCK_WAVE,             //!< 衝撃波エフェクト
    FORECAST_LINE,          //!< 大砲の砲撃予測線
    BARRIER,                //!< スキルによるバリアエフェクト
    FLOATING,               //!< 浮遊エフェクト
    GRAVITY_AREA,           //!< 重力エリアエフェクト
    STRONG_WIND,            //!< 強風エフェクト
    SKILL_STAR,             //!< スキル発動時の共通エフェクト
    OGRE_CONTROL,           //!< 鬼操作のエフェクト
    DEBUFF,                 //!< デバフエフェクト
    RESURRECT,              //!< 復活エフェクト
};
