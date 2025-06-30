#pragma once
#include "../gimmick_component.h" // 親クラスであるGimmickComponentをインクルード
#include "../../../../engine/utility/timer/timer.h"

class FallGimmickComponent : public GimmickComponent
{
public:
    FallGimmickComponent();
    ~FallGimmickComponent() = default;

    // --- IComponentからのオーバーライド ---
    void OnAttach(CGameObject* owner) override;
    void Update(float delta_time, CGameObject* owner) override;

    // --- このクラス固有のメソッド ---
    void AddReturnTime(float time);

private:
    static const float  m_fall_speed;       //!< 落ちる速度
    static const float  m_return_height;    //!< 元に戻る高さ
    static const float  m_return_time;      //!< 元に戻るまでの時間

    float               m_StartHeight;      //!< 初期の高さ
    float               m_ReturnTime;       //!< 元に戻るまでの時間
    CTimer              m_ReturnTimer;      //!< 戻るまでのタイマー
};