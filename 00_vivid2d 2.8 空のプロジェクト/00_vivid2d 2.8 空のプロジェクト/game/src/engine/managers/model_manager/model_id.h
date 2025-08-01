#pragma once

/*!
 *  @brief      ユニット識別ID
 */
enum class MODEL_CATEGORY
{
    UNKNOWN,   //!< 所属不明
};

/*!
 *  @brief      モデルID
 */
enum class MODEL_ID
{
    PLAYER,
    BULLET,
    CUBE,
    FLAT_CUBE,
    CANNON,
    BARRIER,
    OGRE,
    FALLOUT_FLOOR,
    DODGEBALL_STAGE,
    DARUMA_STAGE,
    BELT_CONVEYOR_STAGE,
    BELT_CONVEYOR_OBSTRUCTION_1,
    BELT_CONVEYOR_OBSTRUCTION_2,
    BELT_CONVEYOR_OBSTRUCTION_3,
    BELT_CONVEYOR_OBSTRUCTION_4,
    BELT_CONVEYOR_OBSTRUCTION_5,
    BELT_CONVEYOR_OBSTRUCTION_6,
    SKILL_BARRIER_COLLIDER,
    SKILL_MIMICRY_OBJ,
    SKILL_WALL,
    STOMP_COLL,                     //!< 衝撃波の判定用モデル
    MAX
};