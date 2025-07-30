#include "gimmick_component.h" // 対応するヘッダーファイル
#include "../../../engine/core/game_object/game_object.h"

GimmickComponent::GimmickComponent()
    : m_State(GIMMICK_STATE::WAIT)
    , m_Timer()
{
    // IComponentのコンストラクタで m_IsActive は true に初期化される想定
}

void GimmickComponent::Update(float delta_time, CGameObject* owner)
{
    // 派生クラスで Update が実装されてもタイマーは共通で更新したい場合、
    // 派生クラスの Update の先頭で GimmickComponent::Update(delta_time, owner); を呼ぶ
    m_Timer.Update(); // 元のCTimerがdelta_timeを引数に取らない場合
    // m_Timer.Update(delta_time); // delta_timeで更新する場合
}

void GimmickComponent::SetTimer(float time)
{
    m_Timer.SetUp(time);
}
