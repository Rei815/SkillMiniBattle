#pragma once
#include "../../mathematics/vector/vector3/vector3.h"

struct CollisionResult
{
    bool isHit = false;         // 衝突したか
    CVector3 hitPosition;       // 衝突した座標
    CVector3 hitNormal;         // 衝突点の法線ベクトル
    // 必要なら、ここに他の情報（めり込み量など）を追加できる
};