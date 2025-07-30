#pragma once
#include "../../core/component/component.h"
#include "../../managers/model_manager/model_id.h" // MODEL_ID を使うため
#include "DxLib.h"

class TransformComponent;

class ModelComponent : public IComponent
{

public:

	/*!
	 *  @brief      コンストラクタ
	 *  @param[in]  id             モデルID
	 *  @param[in]  IsDuplicate    複製フラグ
	 */
    ModelComponent(MODEL_ID id = MODEL_ID::MAX, bool IsDuplicate = false);

	/*!
	 *  @brief      デストラクタ
	 */
    ~ModelComponent() override = default;

	/*!
	 *  @brief      アタッチ時の初期化
	 *  @param[in]  owner          コンポーネントをアタッチしたオーナーオブジェクト
	 */
    void OnDetach(CGameObject* owner) override;

    /*!
	 *  @brief      更新
     * 
	 *  @param[in]  delta_time     前フレームからの経過時間
	 *  @param[in]  owner          コンポーネントをアタッチしたオーナーオブジェクト
     */
    void Update(float delta_time, CGameObject* owner) override {};

    /*!
	 *  @brief      描画
     *  
	 *  @param[in]  owner          コンポーネントをアタッチしたオーナーオブジェクト
     */
    void Draw(const CGameObject* owner) const;

    /*!
	 *  @brief      モデルハンドルを設定
     *  
	 *  @param[in]  handle モデルハンドル
     */
    void SetModelHandle(int handle);

	/*!
	 *  @brief      モデルハンドルを取得
     * 
	 *  @return     モデルハンドル
     */ 
    int GetHandle() const;

    /*!
	 *  @brief      マテリアルの色を設定
     *  
	 *  @param[in]  material_index マテリアルのインデックス
	 *  @param[in]  color          設定する色
     */
    void SetMaterialColor(int material_index, const DxLib::COLOR_F& color);

    /*!
	 *  @brief	  マテリアルの色を取得
     *  
	 *  @param[in]  material_index マテリアルのインデックス
     * 
	 *  @return     マテリアルの色
     */
    DxLib::COLOR_F GetMaterialColor(int material_index);

	/*!
	 *  @brief      アルファ値を設定
     * 
	 *  @param[in]  alpha 透明度の値
     */
    void SetAlpha(float alpha);
private:
	int m_ModelHandle;		//!< モデルのハンドル
    float m_Alpha;			//!< 透明度
	bool m_IsDuplicated;	//!< 複製フラグ
};