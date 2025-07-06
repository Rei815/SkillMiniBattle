#pragma once
#include "../../../engine/core/component/component.h"
#include "../../../engine/utility/timer/timer.h"
// ギミックの状態を定義
enum class GIMMICK_STATE
{
    WAIT,
    PLAY,
    FINISH,
};

class GimmickComponent : public IComponent
{
public:
    GimmickComponent();
    virtual ~GimmickComponent() = default;

    void Update(float delta_time, CGameObject* owner) override;

    GIMMICK_STATE GetState() const;
    void SetState(GIMMICK_STATE state);
    void SetTimer(float time);


protected:
    GIMMICK_STATE m_State;
    CTimer        m_Timer;
};