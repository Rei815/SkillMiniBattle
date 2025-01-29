#pragma once

 /*!
  *  @brief      エフェクトID
  */
enum class EFFECT_ID
{
    DESTROY,                //!< 撃破エフェクト
    HIT,                    //!< ヒットエフェクト
    HIT_INVINCBLE,          //!< ヒットエフェクト(無敵中)
    DAMAGE,                 //!< ダメージエフェクト
    JUMP,                   //!< ジャンプエフェクト
    DUST_CLOUD,             //!< 土煙エフェクト
    EMERGENCY,              //!< 警告エフェクト
    SHOCK_WAVE,             //!< 衝撃波エフェクト
    PLAYER_BULLET,          //!< プレイヤー弾エフェクト
    ENEMY_BULLET,           //!< エネミー弾エフェクト
    FORECAST_LINE,          //!< 大砲の砲撃予測線
    SKILL_BARRIER,          //!< スキルによるバリアエフェクト
    FLOATING,               //!< 浮遊エフェクト
    GRAVITY_AREA,           //!< 重力エリアエフェクト
};
