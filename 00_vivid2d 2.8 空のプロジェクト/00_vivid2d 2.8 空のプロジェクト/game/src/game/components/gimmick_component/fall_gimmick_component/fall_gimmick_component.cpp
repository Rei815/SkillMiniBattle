#include "fall_gimmick_component.h" // 対応するヘッダーファイル
#include "../../../../engine/components/transform_component/transform_component.h"
#include "../../../../engine/components/model_component/model_component.h"
#include "../../../../engine/core/game_object/game_object.h"
#include "../../../../engine/components/collider_component/collider_component.h"

const	float				FallGimmickComponent::m_fall_speed = 5.0f;
const	float				FallGimmickComponent::m_return_height = -500.0f;
const	float				FallGimmickComponent::m_return_time = 3.0f;

FallGimmickComponent::FallGimmickComponent()
    : GimmickComponent()
    , m_ReturnTime(m_return_time)
    , m_StartHeight(0.0f)
    , m_ReturnTimer(m_return_time)
{
}

void FallGimmickComponent::OnAttach(CGameObject* owner)
{
    // このコンポーネントがアタッチされた時に一度だけ呼ばれる初期化処理

    // 自分の TransformComponent を取得して、初期の高さを保存する
    auto transform = owner->GetComponent<TransformComponent>();
    if (transform)
    {
        m_StartHeight = transform->GetPosition().y;
    }

    // 各タイマーをセットアップ
    m_Timer.SetUp(m_ReturnTime);
    m_ReturnTimer.SetUp(m_ReturnTime);
}

void FallGimmickComponent::Update(float delta_time, CGameObject* owner)
{
    // 毎フレーム呼ばれる更新処理

    // まず親クラスの共通処理（タイマー更新など）を呼ぶ
    GimmickComponent::Update(delta_time, owner);

    // 連携するコンポーネントを取得
    auto transform = owner->GetComponent<TransformComponent>();
    auto model = owner->GetComponent<ModelComponent>(); // 見た目を管理するコンポーネント

    // TransformComponent がなければ処理を中断
    if (!transform) { return; }

    CVector3 currentPos = transform->GetPosition();

    switch (m_State)
    {
    case GIMMICK_STATE::WAIT:
        // 待機中は何もしない
        break;

    case GIMMICK_STATE::PLAY:
        // 落下処理
        m_Timer.Update();
        if (m_Timer.Finished())
        {
            m_Timer.Reset();
            m_Timer.SetActive(false);

            // 下方向に移動させる（フレームレートに依存しないように delta_time を掛ける）
            transform->Translate(CVector3(0.0f, -m_fall_speed * delta_time, 0.0f));
        }

        // アルファ値（不透明度）を計算して見た目に反映
        if (model)
        {
            float alpha = (currentPos.y - m_return_height) / (m_StartHeight - m_return_height);
            model->SetAlpha(alpha);
        }

        // 特定の高さまで落ちたら当たり判定を無効化
        if (currentPos.y <= (m_StartHeight + m_return_height) * 0.5f)
        {
            if (auto collider = owner->GetComponent<ColliderComponent>()) // 当たり判定コンポーネント
            {
                collider->SetEnabled(false); // 当たり判定をOFFにするメソッドがあると仮定
            }
        }

        // 復帰地点まで落ちたら、状態をFINISHに移行
        if (currentPos.y <= m_return_height)
        {
            m_Timer.SetActive(true);
            m_Timer.SetUp(m_ReturnTime);
            m_State = GIMMICK_STATE::FINISH;
        }
        break;

    case GIMMICK_STATE::FINISH:
        // 復帰処理
        m_ReturnTimer.Update();
        if (m_ReturnTimer.Finished())
        {
            // --- 状態を元に戻す ---
            m_ReturnTimer.Reset();

            // 位置を初期位置に戻す
            currentPos.y = m_StartHeight;
            transform->SetPosition(currentPos);

            // 見た目を元に戻す
            if (model)
            {
                model->SetAlpha(1.0f);
            }

            // 当たり判定を元に戻す
            if (auto collider = owner->GetComponent<ColliderComponent>())
            {
                collider->SetEnabled(true);
            }

            // 待機状態に戻る
            m_State = GIMMICK_STATE::WAIT;
        }
        break;
    }
}

void FallGimmickComponent::AddReturnTime(float time)
{
    m_ReturnTime += time;
    m_ReturnTimer.SetUp(m_ReturnTime);
}