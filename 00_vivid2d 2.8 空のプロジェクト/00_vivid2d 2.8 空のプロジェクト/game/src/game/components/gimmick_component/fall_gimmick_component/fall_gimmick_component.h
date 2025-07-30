#pragma once
#include "../gimmick_component.h" // 親クラスであるGimmickComponentをインクルード
#include "../../../../engine/utility/timer/timer.h"
#include "../../../../engine/managers/ui_manager/ui/fallout_topic/fallout_topic.h"
#include "../../../../engine/managers/object_manager/object_id.h"
class FallGimmickComponent : public GimmickComponent
{
public:
    FallGimmickComponent(OBJECT_ID id);
    ~FallGimmickComponent() = default;

    /*!
     *  @brief      アタッチ時の初期化
     *
     *  @param[in]  owner          コンポーネントをアタッチしたオーナーオブジェクト
     */
    void OnAttach(CGameObject* owner) override;

	/*!
	 *  @brief      更新
	 *
	 *  @param[in] delta_time 前フレームからの経過時間
	 *  @param[in] owner      コンポーネントをアタッチしたオーナーオブジェクト
	 */
    void Update(float delta_time, CGameObject* owner) override;

    /*!
	 *  @brief      戻るまでの時間を加算
     * 
	 *  @param[in] time 加算する値
     * 
     */
    void AddReturnTime(float time);

private:

	static const std::string    m_file_name_list[]; //!< ファイル名リスト
	MARK_ID                     m_MarkID;           //!< マークID  

    static const float  m_fall_speed;               //!< 落ちる速度
    static const float  m_return_height;            //!< 元に戻る高さ
    static const float  m_return_time;              //!< 元に戻るまでの時間

    float               m_StartHeight;              //!< 初期の高さ
    float               m_ReturnTime;               //!< 元に戻るまでの時間
    CTimer              m_ReturnTimer;              //!< 戻るまでのタイマー
};