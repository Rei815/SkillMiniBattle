#pragma once

// 前方宣言: CGameObject クラス
// Component が CGameObject のメソッドを呼び出す必要がある場合があるため
class CGameObject;

// IComponent 基底インターフェース
// 全てのコンポーネントはこのインターフェースを継承する
class IComponent {
public:
    virtual ~IComponent() = default;

    // 更新処理
    // delta_time: 前のフレームからの経過時間（秒単位など）
    // owner: このコンポーネントがアタッチされている GameObject のポインタ
    // コンポーネントが owner の状態を更新するために使用
    virtual void Update(float delta_time, CGameObject* owner) = 0;

    // コンポーネントがエンティティにアタッチされたときに呼ばれる初期化処理
    // ここで、他のコンポーネントへの参照を取得したり、初期設定を行ったりできる
    virtual void OnAttach(CGameObject* owner) { /* デフォルトでは何もしない */ }

    // コンポーネントがエンティティからデタッチされるときに呼ばれる終了処理
    // リソースの解放などを行う
    virtual void OnDetach(CGameObject* owner) { /* デフォルトでは何もしない */ }
};