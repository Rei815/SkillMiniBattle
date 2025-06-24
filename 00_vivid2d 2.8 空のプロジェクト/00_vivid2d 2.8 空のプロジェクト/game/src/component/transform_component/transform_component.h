#pragma once
#include "../component.h"      // IComponent の基底クラス
#include "../../utility/transform/transform.h"
class TransformComponent : public IComponent
{
public:
    // このコンポーネントが保持するデータ
    CTransform transform;

public:
    // コンストラクタ
    TransformComponent() = default;

    // デストラクタ
    ~TransformComponent() override = default;

    // このコンポーネントは、自分自身で何かを更新する必要はないので、
    // Updateの中身は空でOKです。
    // 他のコンポーネントが、このTransformComponentの情報を参照して動作します。
    void Update(float delta_time, CGameObject* owner) override
    {
        // 何もしない
    }
};