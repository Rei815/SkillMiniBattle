#include "shadow_component.h"
#include "engine/core/game_object/game_object.h"
#include "engine/components/transform_component/transform_component.h"
#include <engine/components/collider_component/collision_result.h>
#include <engine/managers/object_manager/object_manager.h>
const float ShadowComponent::m_shadow_max_height = 500.0f;
const float ShadowComponent::m_shadow_min_scale = 0.3f;

const std::string ShadowComponent::m_file_name = "data\\Textures\\shadow.png";
ShadowComponent::ShadowComponent()
{
}

void ShadowComponent::OnAttach(CGameObject* owner)
{
	m_Owner = owner;
    m_Plane = std::make_unique<CPlane>();
    m_Plane->SetUp(m_file_name);
}

void ShadowComponent::Draw()
{
    auto transform = m_Owner->GetComponent<TransformComponent>();
    if (!transform || !m_Plane)
    {
        return;
    }

    CVector3 ownerPos = transform->GetPosition();

    //レイ（線分）の始点と終点を定義
    CVector3 rayStartPos = ownerPos;
	const float max_ray_length = 10000.0f; // レイの最大長さ
    CVector3 rayEndPos = CVector3(ownerPos.x, ownerPos.y - max_ray_length, ownerPos.z); // 真下の十分に遠い位置

    //レイキャストを実行
    CollisionResult hitResult; 
    auto hitObject = CObjectManager::GetInstance().CheckHitLineForAll(
        rayStartPos,
        rayEndPos,
        m_Owner, // 自分自身は当たり判定から除外
        hitResult
    );

	// 衝突した場合のみ影を描画
    if (hitObject != nullptr)
    {
        CVector3 groundPos = hitResult.hitPosition;
        // 高さを計算する処理を元に戻します
        float height = CVector3::Length(ownerPos - groundPos);
        // 高さに応じて影の拡大率を計算する処理を元に戻します
        float scale = 1.0f - (height / m_shadow_max_height);
        if (scale < m_shadow_min_scale) { scale = m_shadow_min_scale; }
        if (scale > 1.0f) { scale = 1.0f; }
        // --- 描画処理 ---
        CTransform planeTransform;
        planeTransform.scale = CVector3(scale, scale, 1.0f);
        m_Plane->SetTransform(planeTransform);

        // 2. 地面の法線ベクトル（レイの衝突結果から取得）
        VECTOR groundNormal = hitResult.hitNormal;

        // 3. 2つのベクトルから回転クォータニオンを生成し、行列に変換する
        //    (CreateLookAt的な考え方で、CVector3::UPをgroundNormalに向ける回転を計算)
        CMatrix slopeRotMat = MGetRotVec2(CVector3::UP, groundNormal);

        // CPlane自体がXY平面（法線がZ軸）なので、まずX軸で90度回転させて地面と平行にする
        CMatrix rotXMat = DxLib::MGetRotX(DX_PI_F / 2.0f);

        // 影の位置を決めるための移動行列
        CMatrix transMat = DxLib::MGetTranslate(CVector3(ownerPos.x, groundPos.y, ownerPos.z));

        // 全ての行列を合成！順番が重要です。
        // スケールはCPlane内部で適用されるので、ここでは不要
        // 1. XY平面のPlaneをXZ平面にする回転 -> 2. 地面の傾きに合わせる回転 -> 3. 指定位置へ移動
        CMatrix worldMat = rotXMat * slopeRotMat * transMat;

		SetWriteZBuffer3D(FALSE); // Zバッファへの書き込みを有効にする
        
        // 3. 影を描画
        m_Plane->Draw(worldMat);
		SetWriteZBuffer3D(TRUE); // Zバッファへの書き込みを無効にする
    }
}