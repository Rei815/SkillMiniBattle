#pragma once
#include "..\..\mathematics\mathematics.h"

class CTransform
{
public:

    CVector3 position;
    CVector3 rotation;
    CVector3 scale;

    /*
    CVector3 forward;
    CVector3 right;
    CVector3 up;
    */

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
    
    /*!
    *  @brief       指定の軸を中心に回転(フレーム)
    *
    *  @param[in]   handle       モデルのハンドル
    *  @param[in]   frameIndex   フレームの番号
    *  @param[in]   point        軸の座標
    *  @param[in]   axis         回転軸
    *  @param[in]   angle        角度
    *
    */
    void            RotateAround(int handle, int frameIndex, const CVector3& point, const CVector3& axis, float angle);

    /*!
    *  @brief       指定の軸を中心に回転
    *
    *  @param[in]   point        軸の座標
    *  @param[in]   axis         回転軸
    *  @param[in]   angle        角度
    *  @param[in]   initPos      初期位置
    *
    */
    void            RotateAround(const CVector3& point, const CVector3& axis, float angle, const CVector3& initPos);
    /*!
    *  @brief       指定の軸を中心に回転
    *
    *  @param[in]   point        軸の座標
    *  @param[in]   axis         回転軸
    *  @param[in]   speed        回転速度
    *
    */
    void            RotateAround(const CVector3& point, const CVector3& axis, float rotateSpeed);
    /*!
    *  @brief       指定の軸を中心に回転(行列)
    *
    *  @param[in]   point        軸の座標
    *  @param[in]   axis         回転軸
    *  @param[in]   speed        回転速度
    *  @return      行列クラス
    *
    */
    CMatrix         GetRotateAroundMatrix(const CVector3& point, const CVector3& axis, CMatrix& mulMat, CMatrix& tranMat, CMatrix& rotMat, float rotateSpeed, float angle);

    /*!
    *  @brief       親のトランスフォームを設定
    *
    *  @param[in]   transform        親のトランスフォーム
    *
    */
    void            SetParent(CTransform* transform);

private:
    CVector3 GetRotateVector(CVector3 vector);

    CVector3 center;
    CVector3 angle;
    CVector3 scaling;
    CTransform* m_Parent;
};