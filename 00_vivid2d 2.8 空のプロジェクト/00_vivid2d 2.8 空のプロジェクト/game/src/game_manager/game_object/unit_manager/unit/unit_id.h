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
    NORMAL_ENEMY,       //!< �ʏ�e�̓G
    THREE_WAY_ENEMY,    //!< 3WAY�e�̓G
    FIVE_WAY_ENEMY,     //!< 5WAY�e�̓G
    BURST_ENEMY,        //!< �o�[�X�g�e�̓G
    SHOTGUN_ENEMY,      //!< �U�e�̓G
    HOMING_ENEMY,       //!< �z�[�~���O�e�̓G
    BOSS_ENEMY,         //!< �{�X�̓G
    PLAYER2,            //!< �v���C���[2
    PLAYER3,            //!< �v���C���[3
    PLAYER4,            //!< �v���C���[4

};

enum class MOVE_ID
{
    LEFT,
    WAIT,
    RIGHT,
};

