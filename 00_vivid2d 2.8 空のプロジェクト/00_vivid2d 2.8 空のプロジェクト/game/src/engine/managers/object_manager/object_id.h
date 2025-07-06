#pragma once
enum class OBJECT_ID
{
    NONE, // 無効なID

    // --- プレイヤーとして操作するオブジェクト ---
    PLAYER,
    // --- 落下オブジェクト ---
    FALL_FLOOR_CIRCLE,
    FALL_FLOOR_CROSS,
    FALL_FLOOR_MOON,
    FALL_FLOOR_SQUARE,
    FALL_FLOOR_SUN,
    FALL_FLOOR_TRIANGLE,

    // --- ステージ構成物 ---
    CANNON,
    BELT_CONVEYOR,
    BELT_CONVEYOR_OBSTRUCTION_1,
    BELT_CONVEYOR_OBSTRUCTION_2,
    BELT_CONVEYOR_OBSTRUCTION_3,
    BELT_CONVEYOR_OBSTRUCTION_4,
    BELT_CONVEYOR_OBSTRUCTION_5,
    BELT_CONVEYOR_OBSTRUCTION_6,
    DARUMA_FALLDOWN_STAGE,
    DODGEBALL_STAGE,
    FALL_OUT_FLOOR,
    OGRE,

    // --- スキルによって生成されるオブジェクト ---
    SKILL_WALL,
    SKILL_MIMICRY_OBJECT,
    SKILL_BARRIER_OBJECT,
    // --- スキルによって生成されるオブジェクト ---
    FALL_GIMMICK,               //!< 落下ギミック
    DARUMA_FALLDOWN_GIMMICK,    //!< だるまさんが転んだギミック
    DODGEBALL_GIMMICK,          //!< ドッジボールギミック
    BELT_CONVEYOR_GIMMICK,      //!< ベルトコンベアギミック
    MAX,                        //!< IDの総数
};