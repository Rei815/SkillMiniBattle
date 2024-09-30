#pragma once
#include "..\..\mathematics\mathematics.h"
class CTransform
{
public:

    CVector3 position;
    CVector3 rotation;
    CVector3 scale;
    CVector3 forward;
    CVector3 right;
    CVector3 up;

    /*!
     *  @brief  コンストラクタ
     */
    CTransform();

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

private:

    CVector3 center;
    CVector3 angle;
    CVector3 scaling;

};