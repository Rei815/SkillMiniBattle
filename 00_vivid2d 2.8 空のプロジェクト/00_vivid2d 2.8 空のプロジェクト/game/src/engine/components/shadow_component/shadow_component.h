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

    static const float m_shadow_max_height;
    static const float m_shadow_min_scale;
	static const std::string m_file_name; //!> 影の画像ファイル名

};