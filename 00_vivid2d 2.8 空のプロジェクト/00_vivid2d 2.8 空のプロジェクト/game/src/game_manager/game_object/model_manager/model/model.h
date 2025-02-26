#pragma once

#include "vivid.h"
#include "model_id.h"
#include "..\..\..\..\utility\utility.h"

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
	 *  @param[in]  position    位置
	 */
	void    Initialize(const std::string& file_name, const CVector3& position, float scale = 1.0f);
	void    Initialize(const std::string& file_name, const CVector3& position, const CVector3& scale);

	void    Initialize(const std::string& file_name, const CTransform& transform, float scale = 1.0f);
	void    Initialize(const std::string& file_name, const CTransform& transform, const CVector3& scale);

	void	Load(const std::string& file_name);

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

	bool CheckHitLine(const CVector3& startPos, const CVector3& endPos);
	bool CheckHitTriangle(const CVector3& posA, const CVector3& posB, const CVector3& posC);
	CVector3 GetHitLinePosition(const CVector3& startPos, const CVector3& endPos);
	CVector3 GetHitTrianglePosition(const CVector3& posA, const CVector3& posB, const CVector3& posC);

	unsigned int GetMaterialDif(int material_index);

	void	SetMaterialDif(int material_index, unsigned int color);
private:
	int			m_Handle;			//!< ハンドル

	CTransform m_Transform;
};