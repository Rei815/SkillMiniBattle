#pragma once
#include "../../../../engine/core/component/component.h"
#include <memory>

class CBeltConveyorGimmick;

class BeltConveyorGimmickComponent : public IComponent
{
public:

	/*!
	 *  @brief      コンストラクタ
	 */
    BeltConveyorGimmickComponent();

	/*!
	 *  @brief      デストラクタ
	 */
    ~BeltConveyorGimmickComponent();

	/*!
	 *  @brief      アタッチ時の初期化
	 *
	 *  @param[in]  owner          コンポーネントをアタッチしたオーナーオブジェクト
	 */
    void OnAttach(CGameObject* owner) override;

	/*！
	 *	@brief      更新
	 *	
	 *	@param[in] delta_time 前フレームからの経過時間
	 *	@param[in] owner      コンポーネントをアタッチしたオーナーオブジェクト
	 */
    void Update(float delta_time, CGameObject* owner) override;

private:
    std::unique_ptr<CBeltConveyorGimmick> m_GimmickLogic;
};