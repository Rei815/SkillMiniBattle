#include "shadow_component.h"
#include "engine/core/game_object/game_object.h"
#include "engine/components/transform_component/transform_component.h"
#include <engine/components/collider_component/collision_result.h>
#include <engine/managers/object_manager/object_manager.h>
// 定数の実体を定義
const float ShadowComponent::m_ground_y = 0.0f;
const float ShadowComponent::m_shadow_max_height = 500.0f;
const float ShadowComponent::m_shadow_base_size = 50.0f; // CPlaneが画像サイズを元にするため、これは使いません
const float ShadowComponent::m_shadow_min_scale = 0.3f;

ShadowComponent::ShadowComponent()
{
}

void ShadowComponent::OnAttach(CGameObject* owner)
{
	m_Owner = owner;
    m_Plane = std::make_unique<CPlane>();
    m_Plane->SetUp("data\\Textures\\shadow.png");
}

void ShadowComponent::Draw()
{
    auto transform = m_Owner->GetComponent<TransformComponent>();
    if (!transform || !m_Plane)
    {
        return;
    }

    // --- CObjectManager を使ったレイキャスト ---
    CVector3 ownerPos = transform->GetPosition();

    // 1. レイ（線分）の始点と終点を定義
    CVector3 rayStartPos = ownerPos;
    CVector3 rayEndPos = CVector3(ownerPos.x, ownerPos.y - 10000.0f, ownerPos.z); // 真下の十分に遠い位置

    // 2. CObjectManager を使ってレイキャストを実行！
    CollisionResult hitResult; // 衝突結果を格納する構造体
    auto hitObject = CObjectManager::GetInstance().CheckHitLineForAll(
        rayStartPos,
        rayEndPos,
        m_Owner, // 自分自身は当たり判定から除外
        hitResult
    );

    // 3. 交点情報を利用
    if (hitObject != nullptr) // レイが何かに当たったか？
    {
        VECTOR groundPos = hitResult.hitPosition;
        float height = VSize(VSub(ownerPos, groundPos));

        // --- 影の色の計算 ---
        // 高さに応じて影の濃さを計算 (0.0f = 黒, 1.0f = 白)
        float color_val_f = height / m_shadow_max_height;
        if (color_val_f > 1.0f) { return; } // 最大高度を超えたら描画しない
        if (color_val_f < 0.0f) { color_val_f = 0.0f; }

        // 0-255の整数値に変換
        unsigned char color_val = (unsigned char)(255.0f * color_val_f);

        // 高さに応じて影の拡大率を計算
        float scale = 1.0f - color_val_f;
        if (scale < m_shadow_min_scale) { scale = m_shadow_min_scale; }
        if (scale > 1.0f) { scale = 1.0f; }

        // --- 描画処理 ---
        CTransform planeTransform;
        planeTransform.scale = VGet(scale, scale, 1.0f);
        m_Plane->SetTransform(planeTransform);

        // 高さに応じて色を設定 (低いほど黒く、高いほど白く)
        m_Plane->SetColor(GetColorU8(color_val, color_val, color_val, 255));

        // 【ここからが新しい処理】
        // 1. 本来の上方向ベクトル
        VECTOR upVec = CVector3(0.0f, 1.0f, 0.0f);

        // 2. 地面の法線ベクトル（レイの衝突結果から取得）
        VECTOR groundNormal = hitResult.hitNormal;

        // 3. 2つのベクトルから回転クォータニオンを生成し、行列に変換する
        //    (CreateLookAt的な考え方で、upVecをgroundNormalに向ける回転を計算)
        CMatrix slopeRotMat = MGetRotVec2(upVec, groundNormal);

        // CPlane自体がXY平面（法線がZ軸）なので、まずX軸で90度回転させて地面と平行にする
        CMatrix rotXMat = DxLib::MGetRotX(DX_PI_F / 2.0f);

        // 影の位置を決めるための移動行列
        CMatrix transMat = DxLib::MGetTranslate(CVector3(ownerPos.x, groundPos.y + 0.5f, ownerPos.z)); // 少し多めに浮かせる

        // 全ての行列を合成！順番が重要です。
        // スケールはCPlane内部で適用されるので、ここでは不要
        // 1. XY平面のPlaneをXZ平面にする回転 -> 2. 地面の傾きに合わせる回転 -> 3. 指定位置へ移動
        CMatrix worldMat = rotXMat * slopeRotMat * transMat;

        // ▼▼▼ 描画モードを修正 ▼▼▼
        SetWriteZBuffer3D(TRUE); // Z書き込みは有効のまま！
        SetDrawBlendMode(DX_BLENDMODE_MULA, 255); // 乗算ブレンドに変更！

        m_Plane->Draw(worldMat);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
    // レイが当たらなかった場合 (else) は、何もしないので影は描画されない
}