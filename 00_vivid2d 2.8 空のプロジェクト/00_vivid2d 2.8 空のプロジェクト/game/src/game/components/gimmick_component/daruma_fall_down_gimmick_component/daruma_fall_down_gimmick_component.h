#pragma once
#include "../../../../engine/core/component/component.h"
#include "../gimmick_component.h"
#include <memory>

// 元のクラスを前方宣言
class CDarumaFallDownGimmick;

class DarumaFallDownGimmickComponent : public GimmickComponent
{
public:
    DarumaFallDownGimmickComponent();
    ~DarumaFallDownGimmickComponent();

    void OnAttach(CGameObject* owner) override;
    void Update(float delta_time, CGameObject* owner) override;

private:
    // 元のギミックのロジックを持つインスタンス
    std::unique_ptr<CDarumaFallDownGimmick> m_GimmickLogic;
};