#pragma once
#include "../../../../engine/core/component/component.h"
#include <memory>
#include "dodge_ball_gimmick/dodge_ball_gimmick.h"

class CDodgeBallGimmick;

class DodgeBallGimmickComponent : public IComponent
{
public:

	/*!
	 *  @brief      コンストラクタ
	 */
    DodgeBallGimmickComponent();

	/*!
	 *  @brief      デストラクタ
	 */
    ~DodgeBallGimmickComponent();

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

    /*
	 *  @brief      操作フラグを設定
     * 
	 *  @param[in] flag 操作フラグ
     */
    void SetOperationFlag(bool flag);

	/*!
	 *  @brief      現在の状態を取得
	 *
	 *  @return     現在の状態
	 */
    CANNON_STATE    GetNowState();

	/*
	 *	@brief      ショットフラグを取得
	 */
    bool            GetShotFlag();

private:
    // 元のギミックのロジックを持つインスタンス
    std::unique_ptr<CDodgeBallGimmick> m_GimmickLogic;
};