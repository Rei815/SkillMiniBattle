#pragma once

 /*!
  *  @brief      ���j�b�g����ID
  */
enum class UNIT_CATEGORY
{
    UNKNOWN,         //!< �����s��
    PLAYER,         //!< �v���C���[
    ENEMY,          //!< �G
};

/*!
 *  @brief      ���j�b�gID
 */
enum class UNIT_ID
{
    PLAYER1,            //!< �v���C���[1
    PLAYER2,            //!< �v���C���[2
    PLAYER3,            //!< �v���C���[3
    PLAYER4,            //!< �v���C���[4
    NONE,
};

enum class MOVE_ID
{
    LEFT,
    WAIT,
    RIGHT,
};

