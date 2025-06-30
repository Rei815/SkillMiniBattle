#pragma once
#include "../component.h"
#include "../../utility/timer/timer.h"

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

    void OnAttach(CGameObject* owner) override;
    void Update(float delta_time, CGameObject* owner) override;

    GIMMICK_STATE GetState() const;
    void SetState(GIMMICK_STATE state);
    virtual void SetOperationFlag(bool flag);

protected:
    GIMMICK_STATE m_State;
    bool          m_OperationFlag;
    CTimer        m_Timer;
};