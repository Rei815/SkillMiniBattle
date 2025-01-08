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
	GRAVITY_AREA,
	INVISIBLE,
	STUN,
	MIMICRY,
	SLOW,
	OGRE_CONTOROL,
	RESURRECT_DARUMA,
	RESURRECT_FALLOUT,
	STRONG_WIND,

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
	STRONG_WIND,

	MAX,
};

/*!
 *  @brief      ����܂��񂪂���񂾂̃X�L��ID
 */
enum class SKILL_ID_DARUMA
{
	SPEED_UP,
	INVISIBLE,
	STUN,
	MIMICRY,
	SLOW,
	OGRE_CONTOROL,
	RESURRECT_DARUMA,

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
	GRAVITY_AREA,

	MAX,
};