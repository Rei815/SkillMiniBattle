#pragma once

/*!
 *  @brief      スキル識別ID
 */
enum class SKILL_CATEGORY
{
	UNKNOWN,        //!< 所属不明
	ACTIVE,         //!< アクティブ
	PASSIVE,        //!< パッシブ
};

/*!
 *  @brief      スキルID
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
 *  @brief      フォールアウトのスキルID
 */
enum class SKILL_ID_FALLOUT
{
	SPEED_UP,
	JUMP_UP,
	FLOATING,
	STRONG_WIND,
	STOMP,
	RESURRECT,
	HIDE_TOPIC,
	MAX,

};

/*!
 *  @brief      だるまさんがころんだのスキルID
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
 *  @brief      ドッジボールのスキルID
 */
enum class SKILL_ID_DODGEBALL
{
	SPEED_UP,
	JUMP_UP,
	DASH,
	SPAWN_WALL,
	BARRIER,
	GRAVITY_AREA,
	FLOATING,
	STRONG_WIND,

	MAX,

};

/*!
 *  @brief      ベルトコンベアのスキルID
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


/*!
 *  @brief      迷路のスキルID
 */
enum class SKILL_ID_MAZE
{
	SPEED_UP,
	JUMP_UP,
	SPAWN_WALL,
	STOMP,
	MAX,
	DASH,
	GRAVITY_AREA,

	INVISIBLE,
	BARRIER,
	FLOATING,
	STRONG_WIND,

};