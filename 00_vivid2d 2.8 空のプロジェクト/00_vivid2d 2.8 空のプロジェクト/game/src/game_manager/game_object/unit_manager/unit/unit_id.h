#pragma once

 /*!
  *  @brief      ユニット識別ID
  */
enum class UNIT_CATEGORY
{
    UNKNOWN,         //!< 所属不明
    PLAYER,         //!< プレイヤー
    ENEMY,          //!< 敵
};

/*!
 *  @brief      ユニットID
 */
enum class UNIT_ID
{
    NONE,
    PLAYER1,            //!< プレイヤー1
    NORMAL_ENEMY,       //!< 通常弾の敵
    THREE_WAY_ENEMY,    //!< 3WAY弾の敵
    FIVE_WAY_ENEMY,     //!< 5WAY弾の敵
    BURST_ENEMY,        //!< バースト弾の敵
    SHOTGUN_ENEMY,      //!< 散弾の敵
    HOMING_ENEMY,       //!< ホーミング弾の敵
    BOSS_ENEMY,         //!< ボスの敵
    PLAYER2,            //!< プレイヤー2
    PLAYER3,            //!< プレイヤー3
    PLAYER4,            //!< プレイヤー4

};

enum class MOVE_ID
{
    LEFT,
    WAIT,
    RIGHT,
};

