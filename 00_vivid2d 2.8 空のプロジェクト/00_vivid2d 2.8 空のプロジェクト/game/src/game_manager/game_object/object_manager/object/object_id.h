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
    MAX,
};
