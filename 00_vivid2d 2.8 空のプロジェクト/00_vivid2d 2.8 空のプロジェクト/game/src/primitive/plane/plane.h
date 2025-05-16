#pragma once
#include "vivid.h"
#include "..\..\mathematics\mathematics.h"
#include "..\..\utility\utility.h"


class CPlane
{
public:

	CPlane();

	~CPlane();

	/*!
	 *  @brief      初期設定
	 *  @param[in]	fileName	画像のファイル名
	 */
	void SetUp(const std::string fileName);

	void _Draw();

	/*!
	 *  @brief      行列を渡して描画する
	 *  @param[in]	mat	行列
	 */
	void Draw(const CMatrix& mat);

	/*!
	 *  @brief      解放
	 */
	void Finalize();

	/*!
	 *  @brief      トランスフォームの設定
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