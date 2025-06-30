#pragma once
#include "..\..\mathematics\mathematics.h"

class CTransform
{
public:

    CVector3 position;  //!< 位置
    CVector3 rotation;  //!< 回転
    CVector3 scale;     //!< 大きさ

    /*!
     *  @brief  コンストラクタ
     */
    CTransform();
    /*!
     *  @brief  コンストラクタ
     */
    CTransform(const CVector3& pos);

    /*!
     *  @brief  コンストラクタ
     */
    CTransform(const CVector3& pos, const CVector3& rot);

    /*!
     *  @brief  デストラクタ
     */
    ~CTransform() = default;

    /*!
    *  @brief      代入演算子のオーバーロード
    *
    *  @param[in]  t   トランスフォームクラス
    *
    *  @return     トランスフォームクラス
    */
    CTransform& operator=(const CTransform& t);

    CVector3 GetForwardVector(void);

    CVector3 GetRightVector(void);

    CVector3 GetUpVector(void);

    CVector3 GetRadianRotation(void);

private:
    CVector3 GetRotateVector(CVector3 vector);
};