#include "gimmick_component.h" // 対応するヘッダーファイル

GimmickComponent::GimmickComponent()
    : m_State(GIMMICK_STATE::WAIT)
    , m_OperationFlag(false)
    , m_Timer()
{
    // IComponentのコンストラクタで m_IsActive は true に初期化される想定
}

void GimmickComponent::OnAttach(CGameObject* owner)
{
    // 派生クラスで具体的な初期化を行うため、基底クラスでは何もしない
}

void GimmickComponent::Update(float delta_time, CGameObject* owner)
{
    // 派生クラスで Update が実装されてもタイマーは共通で更新したい場合、
    // 派生クラスの Update の先頭で GimmickComponent::Update(delta_time, owner); を呼ぶ
    m_Timer.Update(); // 元のCTimerがdelta_timeを引数に取らない場合
    // m_Timer.Update(delta_time); // delta_timeで更新する場合
}

GIMMICK_STATE GimmickComponent::GetState() const
{
    return m_State;
}

void GimmickComponent::SetState(GIMMICK_STATE state)
{
    m_State = state;
}

void GimmickComponent::SetOperationFlag(bool flag)
{
    m_OperationFlag = flag;
}