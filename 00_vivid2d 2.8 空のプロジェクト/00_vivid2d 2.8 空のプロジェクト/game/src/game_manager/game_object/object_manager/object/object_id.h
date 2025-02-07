#pragma once

/*!
 *  @brief      オブジェクトID
 */
enum class OBJECT_ID
{
    NONE,                   //!< 空
    MOON_FALL_OBJECT,       //!< 落ちるオブジェクト(月マーク)
    SUN_FALL_OBJECT,        //!< 落ちるオブジェクト(太陽マーク)
    CIRCLE_FALL_OBJECT,     //!< 落ちるオブジェクト(丸マーク)
    SQUARE_FALL_OBJECT,     //!< 落ちるオブジェクト(四角マーク)
    TRIANGLE_FALL_OBJECT,   //!< 落ちるオブジェクト(三角マーク)
    CROSS_FALL_OBJECT,      //!< 落ちるオブジェクト(バツマーク)
    OGRE_OBJECT,            //!< だるまさんが転んだの鬼
    CANNON_OBJECT,          //!< 大砲オブジェクト
    DODGEBALL_STAGE_OBJECT, //!< ドッジボールシーンのステージオブジェクト
    DARUMA_FALLDOWN_STAGE_OBJECT, //!< ドッジボールシーンのステージオブジェクト
    BELT_CONVEYOR_STAGE_OBJECT,   //!< ベルトコンベアのステージオブジェクト
    SKILL_WALL_OBJECT,      //!< スキルでスポーンできる壁オブジェクト
    MAX,
};
