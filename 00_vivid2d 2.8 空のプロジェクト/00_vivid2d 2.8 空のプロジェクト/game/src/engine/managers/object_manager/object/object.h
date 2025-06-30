#pragma once
#include <memory>
#include "object_id.h"

// 前方宣言
class CGameObject;
class CGimmick;
class CTransform;

// すべての「静的オブジェクト」の親となるクラス
// もはや、自分では描画も座標管理もしない、「脳」だけの存在
class IObject
{
protected:
    // ★★★ すべてのオブジェクトが持つ「体」 ★★★
    std::shared_ptr<CGameObject> m_gameObject;

    // --- 「脳」が持つべき、オブジェクト固有のデータ ---
    OBJECT_ID m_ObjectID;
    std::shared_ptr<CGimmick> m_Gimmick;
    std::string m_Tag;
    bool m_ColliderActiveFlag;

public:
    IObject();
    virtual ~IObject() = default;

    // 初期化処理は、自分の「体」を生成し、設定する役割になる
    virtual void Initialize(OBJECT_ID id, const CTransform& transform);

    // 更新処理は、ギミックの更新や、特殊なロジックを実行する
    virtual void Update();

    // 描画処理は、「体」に丸投げするだけ
    virtual void Draw();

    // --- 外部とのインターフェース ---
    // 座標などを知りたい場合は、「体」に問い合わせる
    CVector3 GetPosition();
    bool IsActive();
    void Delete(); // 内部でm_gameObject->Delete()を呼ぶ

    // ギミックの操作は、そのまま残す
    void SetGimmick(std::shared_ptr<CGimmick> gimmick);
    std::shared_ptr<CGimmick> GetGimmick();
};