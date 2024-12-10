#pragma once

/*!
 *  @brief      �X�L������ID
 */
enum class SKILL_CATEGORY
{
	UNKNOWN,        //!< �����s��
	ACTIVE,         //!< �A�N�e�B�u
	PASSIVE,        //!< �p�b�V�u
	RESURRECT,      //!< ����
};


/*!
 *  @brief      �t�H�[���A�E�g�̃X�L��ID
 */
enum class SKILL_ID_FALLGAME
{
	SPEED_UP,
	JUMP_UP,
	FLOATING,
	STOMP,
	RESURRECT,

	MAX,
};

/*!
 *  @brief      ����܂��񂪂���񂾂̃X�L��ID
 */
enum class SKILL_ID_DARUMA
{
	SPEED_UP,
	INVISIBLE,

	MAX,
};

/*!
 *  @brief      �h�b�W�{�[���̃X�L��ID
 */
enum class SKILL_ID_DODGEBALL
{
	SPEED_UP,
	JUMP_UP,
	DASH,
	SPAWN_WALL,
	BARRIER,

	MAX,
};