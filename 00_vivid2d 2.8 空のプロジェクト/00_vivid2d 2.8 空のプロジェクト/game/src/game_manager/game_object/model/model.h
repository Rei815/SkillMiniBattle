#pragma once

#include "vivid.h"
#include "model_id.h"
#include "..\..\..\utility\utility.h"

/*!
 *  @brief      モデルクラス
 */
class CModel
{
public:

	/*!
	 *  @brief  コンストラクタ
	 */
	CModel();

	/*!
	 *  @brief  コンストラクタ
	 */
	~CModel();

	/*!
	 *  @brief      初期化
	 *
	 *  @param[in]  file_name   ファイル名
	 *  @param[in]  position    位置
	 *  @param[in]  scale		大きさ
	 */
	void    Initialize(const std::string& file_name, const CVector3& position, float scale = 1.0f);
	void    Initialize(const std::string& file_name, const CVector3& position, const CVector3& scale);

	/*!
	 *  @brief      初期化
	 *
	 *  @param[in]  file_name   ファイル名
	 *  @param[in]  transform   トランスフォーム
	 *  @param[in]  scale		大きさ
	 */
	void    Initialize(const std::string& file_name, const CTransform& transform, float scale = 1.0f);
	void    Initialize(const std::string& file_name, const CTransform& transform, const CVector3& scale);

	/*!
	 *  @brief      ロード
	 *
	 *  @param[in]  file_name   ファイル名
	 */
	void	Load(const std::string& file_name);

	/*!
	 *  @brief      アンロード
	 */
	void	Unload(void);

	/*!
	 *  @brief      更新
	 */
	void    Update(void);

	/*!
	 *  @brief      更新
	 */
	void    Update(const CTransform& transform);

	/*!
	 *  @brief      描画
	 */
	void    Draw(void);

	/*!
	 *  @brief      解放
	 */
	void    Finalize(void);

	/*!
	*  @brief  ハンドルの呼び出し
	*/
	int GetModelHandle() const;

	/*!
	*  @brief  位置設定
	*/
	void SetPosition(const CVector3& position);

	/*!
	*  @brief  回転設定
	*/
	void SetRotation(const CVector3& rotation);


	/*!
	 *  @brief      拡大設定
	 * 
	 *  @param[in]  scale   セットする拡大の倍率
	 */
	void SetScale(float scale);

	/*!
	 *  @brief      拡大設定
	 * 
	 *  @param[in]  scale   セットする拡大の倍率
	 */
	void SetScale(const CVector3& scale);

	/*!
	 *  @brief      線分と当たっているかをチェック
	 *
	 *  @param[in]  startPos	線分の開始位置
	 *  @param[in]  endPos		線分の最終位置
	 * 
	 *  @return		true 当たっている false 当たっていない
	 */
	bool CheckHitLine(const CVector3& startPos, const CVector3& endPos)const;

	/*!
	 *  @brief      線分と当たった位置を返す
	 *
	 *  @param[in]  startPos	線分の開始位置
	 *  @param[in]  endPos		線分の最終位置
	 *
	 *  @return		当たった位置
	 */
	CVector3 GetHitLinePosition(const CVector3& startPos, const CVector3& endPos)const;

	/*!
	 *  @brief      マテリアルのディフューズカラーを取得
	 *
	 *  @param[in]  material_index  マテリアルの番号
	 * 
	 *  @return		色(16進数)
	 */
	unsigned int GetMaterialDif(int material_index);

	/*!
	 *  @brief      マテリアルのディフューズカラーを設定
	 *
	 *  @param[in]  material_index	マテリアルの番号
	 *  @param[in]  color			色(16進数)
	 */
	void	SetMaterialDif(int material_index, unsigned int color);
private:
	int			m_Handle;			//!< ハンドル
	CTransform m_Transform;			//!< トランスフォーム
};