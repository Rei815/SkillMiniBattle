#pragma once

// 前方宣言: CGameObject クラス
class CGameObject;

// IComponent 基底インターフェース
// 全てのコンポーネントはこのインターフェースを継承する
class IComponent 
{
public:

	/*!
	 *  @brief      デストラクタ
	 */
    virtual ~IComponent() = default;

	/*!
	 *	@brief      コンポーネントの更新
	 * 
	 *	@param[in] delta_time 前フレームからの経過時間
	 *	@param[in] owner      コンポーネントをアタッチしたオーナーオブジェクト
	 */
    virtual void Update(float delta_time, CGameObject* owner) = 0;

    virtual void OnAttach(CGameObject* owner) { /* デフォルトでは何もしない */ }

    virtual void OnDetach(CGameObject* owner) { /* デフォルトでは何もしない */ }
protected:
	CGameObject* m_Owner = nullptr; // このコンポーネントがアタッチされている GameObject のポインタ
};