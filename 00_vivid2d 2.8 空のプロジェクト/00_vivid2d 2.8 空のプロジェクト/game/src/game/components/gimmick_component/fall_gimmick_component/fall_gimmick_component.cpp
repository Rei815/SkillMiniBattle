#include "fall_gimmick_component.h"
#include "../../../../engine/components/transform_component/transform_component.h"
#include "../../../../engine/components/model_component/model_component.h"
#include "../../../../engine/core/game_object/game_object.h"
#include "../../../../engine/components/collider_component/mesh_collider_component/mesh_collider_component.h"

const	float				FallGimmickComponent::m_fall_speed = 300.0f;
const	float				FallGimmickComponent::m_return_height = -500.0f;
const	float				FallGimmickComponent::m_return_time = 3.0f;
const	std::string		FallGimmickComponent::m_file_name_list[] = {
    "data\\Models\\Textures\\fall_out_circle.png",
    "data\\Models\\Textures\\fall_out_cross.png",
    "data\\Models\\Textures\\fall_out_moon.png",
    "data\\Models\\Textures\\fall_out_square.png",
    "data\\Models\\Textures\\fall_out_sun.png",
    "data\\Models\\Textures\\fall_out_triangle.png",
};
FallGimmickComponent::FallGimmickComponent(OBJECT_ID id)
    : GimmickComponent()
    , m_ReturnTime(m_return_time)
    , m_StartHeight(0.0f)
    , m_ReturnTimer(m_return_time)
{
    switch (id)
    {
    case OBJECT_ID::FALL_FLOOR_CIRCLE:		m_MarkID = MARK_ID::CIRCLE;		break;
    case OBJECT_ID::FALL_FLOOR_CROSS:		m_MarkID = MARK_ID::CROSS;		break;
    case OBJECT_ID::FALL_FLOOR_MOON:		m_MarkID = MARK_ID::MOON;		break;
    case OBJECT_ID::FALL_FLOOR_SQUARE:		m_MarkID = MARK_ID::SQUARE;		break;
    case OBJECT_ID::FALL_FLOOR_SUN:		    m_MarkID = MARK_ID::SUN;		break;
    case OBJECT_ID::FALL_FLOOR_TRIANGLE:	m_MarkID = MARK_ID::TRIANGLE;	break;
    }

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

    CVector3 rotation = transform->GetRotation();
    switch (m_MarkID)
    {
    case MARK_ID::CIRCLE:   rotation.y = 30; break;
    case MARK_ID::CROSS:    rotation.y = 30; break;
    case MARK_ID::MOON:     rotation.y = 90; break;
    case MARK_ID::SQUARE:   rotation.y = -30;break;
    case MARK_ID::SUN:      rotation.y = 90; break;
    case MARK_ID::TRIANGLE: rotation.y = -30;break;
    case MARK_ID::NONE:
        break;
    }
    transform->SetRotation(rotation);
    // 各タイマーをセットアップ
    m_ReturnTimer.SetUp(m_ReturnTime);

    auto& FileName = m_file_name_list[static_cast<int>(m_MarkID)];
    vivid::LoadTexture(FileName);

    int grHandle = vivid::core::FindLoadedTexture(FileName);

    auto model = owner->GetComponent<ModelComponent>();
    DxLib::MV1SetTextureGraphHandle(model->GetHandle(), 0, grHandle, true);

    //モデルを半透明に変更
    DxLib::COLOR_F color = model->GetMaterialColor(0);
    //アルファ値をクリアし、100を入れる
    color.a = 0.5f;
    model->SetMaterialColor(0, color);
}

void FallGimmickComponent::Update(float delta_time, CGameObject* owner)
{
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
            if (auto collider = owner->GetComponent<MeshColliderComponent>()) // 当たり判定コンポーネント
            {
                collider->SetEnabled(false); // 当たり判定をOFFにするメソッドがあると仮定
            }
        }

        // 復帰地点まで落ちたら、状態をFINISHに移行
        if (currentPos.y <= m_return_height)
        {
            m_ReturnTimer.SetUp(m_ReturnTime);
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
            if (auto collider = owner->GetComponent<MeshColliderComponent>())
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