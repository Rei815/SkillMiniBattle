#pragma once

 /*!
  *  @brief      ƒ†ƒjƒbƒgŽ¯•ÊID
  */
enum class UNIT_CATEGORY
{
    UNKNOWN,         //!< Š‘®•s–¾
    PLAYER,         //!< ƒvƒŒƒCƒ„[
    ENEMY,          //!< “G
};

/*!
 *  @brief      ƒ†ƒjƒbƒgID
 */
enum class UNIT_ID
{
    PLAYER,             //!< ƒvƒŒƒCƒ„[
    NORMAL_ENEMY,       //!< ’Êí’e‚Ì“G
    THREE_WAY_ENEMY,    //!< 3WAY’e‚Ì“G
    FIVE_WAY_ENEMY,     //!< 5WAY’e‚Ì“G
    BURST_ENEMY,        //!< ƒo[ƒXƒg’e‚Ì“G
    SHOTGUN_ENEMY,      //!< ŽU’e‚Ì“G
    HOMING_ENEMY,       //!< ƒz[ƒ~ƒ“ƒO’e‚Ì“G
    BOSS_ENEMY,         //!< ƒ{ƒX‚Ì“G

};

enum class MOVE_ID
{
    LEFT,
    WAIT,
    RIGHT,
};

