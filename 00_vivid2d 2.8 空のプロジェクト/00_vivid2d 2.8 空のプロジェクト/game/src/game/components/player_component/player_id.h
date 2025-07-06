#pragma once

/*!
 *  @brief      プレイヤー識別ID
 */
enum class PLAYER_CATEGORY
{
    UNKNOWN,        //!< 所属不明
    PLAYER,         //!< プレイヤー
    PLAYER1,        //!< プレイヤー1
    PLAYER2,        //!< プレイヤー2
    PLAYER3,        //!< プレイヤー3
    PLAYER4,        //!< プレイヤー4
};

/*!
 *  @brief      プレイヤーID
 */
enum class PLAYER_ID
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

