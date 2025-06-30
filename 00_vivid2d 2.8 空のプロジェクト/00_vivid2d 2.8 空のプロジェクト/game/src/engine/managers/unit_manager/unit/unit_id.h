#pragma once

 /*!
  *  @brief      ユニット識別ID
  */
enum class UNIT_CATEGORY
{
    UNKNOWN,        //!< 所属不明
    PLAYER,         //!< プレイヤー
    PLAYER1,        //!< プレイヤー1
    PLAYER2,        //!< プレイヤー2
    PLAYER3,        //!< プレイヤー3
    PLAYER4,        //!< プレイヤー4
    ENEMY,          //!< 敵
};

/*!
 *  @brief      ユニットID
 */
enum class UNIT_ID
{
    PLAYER1,            //!< プレイヤー1
    PLAYER2,            //!< プレイヤー2
    PLAYER3,            //!< プレイヤー3
    PLAYER4,            //!< プレイヤー4
    NONE,
};

enum class MOVE_ID
{
    LEFT,
    WAIT,
    RIGHT,
};

