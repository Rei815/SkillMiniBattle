#pragma once

/*!
 *  @brief      �X�L������ID
 */
enum class SKILL_CATEGORY
{
	UNKNOWN,        //!< �����s��
	RESURRECT,      //!< ����
};

/*!
 *  @brief      �X�L��ID
 */
enum class SKILL_ID
{
	SPEED_UP,
	JUMP_UP,
	FLOATING,
	STOMP,
	DASH,
	SPAWN_WALL,
	BARRIER,

	RESURRECT_FALLOUT,

	MAX,
};

/*!
 *  @brief      �t�H�[���A�E�g�̃X�L��ID
 */
enum class SKILL_ID_FALLOUT
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