#pragma once

/*!
 *  @brief      スキル識別ID
 */
enum class SKILL_CATEGORY
{
	UNKNOWN,        //!< 所属不明
	RESURRECT,      //!< 復活
};


/*!
 *  @brief      フォールアウトのスキルID
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
 *  @brief      だるまさんがころんだのスキルID
 */
enum class SKILL_ID_DARUMA
{
	SPEED_UP,

	MAX,
};

/*!
 *  @brief      ドッジボールのスキルID
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