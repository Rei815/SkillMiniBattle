#include "mesh_collider_component.h"
#include "../../../core/game_object/game_object.h"
#include "../../model_component/model_component.h" // ModelComponentからハンドルをもらう

MeshColliderComponent::MeshColliderComponent()
    : m_ModelHandle(-1) // DxLibのハンドルは-1で初期化するのが一般的
{
}

void MeshColliderComponent::OnAttach(CGameObject* owner)
{
    // 自分を所有しているGameObjectにアタッチされているModelComponentを探す
    auto modelComp = owner->GetComponent<ModelComponent>();
    if (modelComp)
    {
        // ModelComponentが見つかったら、そこからモデルハンドルを取得して保持する
        m_ModelHandle = modelComp->GetHandle();

        // 元のCModelにあった当たり判定用のセットアップをここに持ってくる
        if (m_ModelHandle != -1)
        {
            MV1SetupCollInfo(m_ModelHandle, -1, 8, 8, 8);
        }
    }
    else
    {
        // ModelComponentがないと動作しないので、警告を出すなど
        // DX_LOGPRINTF("警告: MeshColliderComponentはModelComponentを必要とします。");
    }
}

void MeshColliderComponent::Update(float delta_time, CGameObject* owner)
{
	// MeshColliderComponentは特に更新処理が必要ないので、空実装
	// ただし、必要に応じてここに何か処理を追加することも可能
	// 例えば、モデルの位置や回転に合わせてコライダーを更新するなど
}

bool MeshColliderComponent::CheckHitLine(const CVector3& startPos, const CVector3& endPos) const
{
    // 衝突位置を格納するが、この関数の結果としては使わない「ダミー変数」
    CVector3 dummy_hit_position;

    // 内部で、引数が多い方の詳細な関数を呼び出し、その結果(true/false)だけを返す
    return this->CheckHitLine(startPos, endPos, dummy_hit_position);
}

bool MeshColliderComponent::CheckHitLine(const CVector3& startPos,const CVector3& endPos, CVector3& out_hitPosition) const
{
    if (m_ModelHandle == -1)
    {
        return false; // ハンドルが無効なら何もしない
    }

    // DXライブラリの当たり判定関数を呼び出す
    MV1_COLL_RESULT_POLY hitPoly = MV1CollCheck_Line(m_ModelHandle, -1, startPos, endPos);

    if (hitPoly.HitFlag) // DxLibのHitFlagはint型 (0 or 1)
    {
        // ヒットした場合、衝突位置をout引数に格納してtrueを返す
        out_hitPosition = hitPoly.HitPosition;
        return true;
    }

    // ヒットしなかった場合
    return false;
}
bool MeshColliderComponent::CheckHitSphere(const CVector3& center, float radius, CollisionResult& out_result) const
{
    if (m_ModelHandle == -1) return false;

    // モデルと球の当たり判定
    DxLib::MV1_COLL_RESULT_POLY_DIM hitResult = MV1CollCheck_Sphere(m_ModelHandle, -1, center, radius);
    // ヒットしたかどうかを bool に変換
    out_result.isHit = (hitResult.HitNum > 0);

    if (out_result.isHit)
    {
        // ヒットした場合、詳細情報を構造体に格納する
        out_result.hitPosition = hitResult.Dim->HitPosition;
        out_result.hitNormal = hitResult.Dim->Normal;
        MV1CollResultPolyDimTerminate(hitResult); // 後始末
        return true;

    }
    // ヒットしなかった場合
    return false;

}

bool MeshColliderComponent::CheckHitCapsule(const CVector3& posA, const CVector3& posB, float radius ,CVector3& out_hitPosition) const
{
    if (m_ModelHandle == -1) return false;

    // モデルとカプセルの当たり判定
    DxLib::MV1_COLL_RESULT_POLY_DIM hitResult = MV1CollCheck_Capsule(m_ModelHandle, -1, posA, posB, radius);
    if (hitResult.HitNum > 0)
    {
        // ヒットした場合、衝突位置をout引数に格納してtrueを返す
        out_hitPosition = hitResult.Dim->HitPosition;

        MV1CollResultPolyDimTerminate(hitResult); // 後始末
        return true;

    }
    // ヒットしなかった場合
    return false;
}