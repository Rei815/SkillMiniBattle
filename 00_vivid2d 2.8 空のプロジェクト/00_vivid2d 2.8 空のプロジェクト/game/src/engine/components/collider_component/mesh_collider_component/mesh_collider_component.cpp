#include "mesh_collider_component.h"
#include "../../../game_manager/game_object/game_object.h"
#include "../../model_component/model_component.h" // ModelComponentからハンドルをもらう
#include <DxLib.h>

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
        m_ModelHandle = modelComp->GetModelHandle();

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

bool MeshColliderComponent::CheckHitLine(
    const CVector3& startPos,
    const CVector3& endPos,
    CVector3& out_hitPosition) const
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