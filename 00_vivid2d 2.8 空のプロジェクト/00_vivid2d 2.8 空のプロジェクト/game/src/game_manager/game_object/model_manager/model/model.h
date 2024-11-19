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
	void    Initialize(const std::string& file_name, const CVector3& position);

	void    Initialize(const std::string& file_name, const CTransform& transform);

	void	Load(const std::string& file_name);

	void	Unload(void);

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

	bool CheckHitLine(const CVector3& startPos, const CVector3& endPos);
	bool CheckHitTriangle(const CVector3& posA, const CVector3& posB, const CVector3& posC);
	CVector3 GetHitLinePosition(const CVector3& startPos, const CVector3& endPos);
	CVector3 GetHitTrianglePosition(const CVector3& posA, const CVector3& posB, const CVector3& posC);
private:
	int			m_Handle;			//!< ハンドル

	CTransform m_Transform;
};