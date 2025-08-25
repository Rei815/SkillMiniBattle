#pragma once
#include "engine/core/component/component.h"
#include "engine/primitive/plane/plane.h"
#include <memory>
class ShadowComponent : public IComponent
{
public:
    ShadowComponent();
	~ShadowComponent() override = default;

    void OnAttach(CGameObject* owner) override;

	void Update(float delta_time, CGameObject* owner) override { /* 更新は不要 */ }
    // このコンポーネントが描画処理を持つことを示す
    void Draw();

private:


    int m_ShadowGraph; // 影の画像ハンドル

    std::unique_ptr<CPlane> m_Plane; // CPlaneクラスのインスタンスを持つ

    // 影の計算に使うパラメータ
    static const float m_ground_y;
    static const float m_shadow_max_height;
    static const float m_shadow_base_size; // CPlaneが画像の大きさを使うので、これは不要になるかも
    static const float m_shadow_min_scale;
};