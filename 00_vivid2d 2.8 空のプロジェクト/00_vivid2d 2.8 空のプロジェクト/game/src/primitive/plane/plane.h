#pragma once
#include "vivid.h"
#include "..\..\mathematics\mathematics.h"
#include "..\..\utility\utility.h"

/*!
 *  @brief  プレーンクラス
 */
class CPlane
{
public:

	/*!
	 *  @brief  コンストラクタ
	 */
	CPlane();

	/*!
	 *  @brief  デストラクタ
	 */
	~CPlane();

	/*!
	 *  @brief      初期設定
	 * 
	 *  @param[in]	fileName	画像のファイル名
	 */
	void SetUp(const std::string fileName);

	/*!
	 *  @brief      描画
	 * 
	 */
	void Draw(const CMatrix& mat);

	/*!
	 *  @brief      解放
	 */
	void Finalize();

	/*!
	 *  @brief      トランスフォームの設定
	 * 
	 *  @param[in]	transform	トランスフォーム
	 */
	void	SetTransform(const CTransform& transform);

private:

	static const unsigned short m_index[];
	CTransform					m_Transform;
	int							m_Handle;
	DxLib::COLOR_U8				m_Color;
	int							m_Width;
	int							m_Height;
	CVector3					m_Normal;
};