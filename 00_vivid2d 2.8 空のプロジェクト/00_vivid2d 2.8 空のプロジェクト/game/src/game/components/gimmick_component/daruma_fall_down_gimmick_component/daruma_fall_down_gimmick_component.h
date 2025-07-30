#pragma once
#include "../../../../engine/core/component/component.h"
#include "../gimmick_component.h"
#include <memory>

class CDarumaFallDownGimmick;

class DarumaFallDownGimmickComponent : public GimmickComponent
{
public:

    /*!
     *  @brief      コンストラクタ
     */
    DarumaFallDownGimmickComponent();

	/*!
	 *  @brief      デストラクタ
	 */
    ~DarumaFallDownGimmickComponent();
    
	/*!
	 *  @brief      アタッチ時の初期化
	 *
	 *  @param[in]  owner          コンポーネントをアタッチしたオーナーオブジェクト
	 */
    void OnAttach(CGameObject* owner) override;

	/*!
	 *  @brief      更新
	 *
	 *  @param[in]  delta_time     前フレームからの経過時間
	 *  @param[in]  owner          コンポーネントをアタッチしたオーナーオブジェクト
	 */
    void Update(float delta_time, CGameObject* owner) override;

	/*!
	 *  @brief      鬼の振り向き
	 */
    void OgreControlTurn();
private:
    // 元のギミックのロジックを持つインスタンス
    std::unique_ptr<CDarumaFallDownGimmick> m_GimmickLogic;
};