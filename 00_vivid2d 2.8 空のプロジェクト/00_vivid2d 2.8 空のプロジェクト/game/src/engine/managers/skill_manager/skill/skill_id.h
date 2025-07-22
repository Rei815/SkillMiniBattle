#pragma once

/*!
 *  @brief      �X�L������ID
 */
enum class SKILL_CATEGORY
{
	UNKNOWN,        //!< �����s��
	ACTIVE,         //!< �A�N�e�B�u
	PASSIVE,        //!< �p�b�V�u
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
	RESURRECT_BELT,
	STRONG_WIND,
	HIDE_TOPIC,
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
	STRONG_WIND,
	RESURRECT,
	HIDE_TOPIC,
	MAX,

};

/*!
 *  @brief      ����܂��񂪂���񂾂̃X�L��ID
 */
enum class SKILL_ID_DARUMA
{
	DASH,
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
	BARRIER,
	MAX,
	SPAWN_WALL,
	GRAVITY_AREA,
	FLOATING,
	STRONG_WIND,


};

/*!
 *  @brief      �x���g�R���x�A�̃X�L��ID
 */
enum class SKILL_ID_BELTCONVEYOR
{
	SPEED_UP,
	JUMP_UP,
	DASH,
	GRAVITY_AREA,
	SLOW,
	FLOATING,
	STRONG_WIND,
	RESURRECT_BELT,

	MAX,

};