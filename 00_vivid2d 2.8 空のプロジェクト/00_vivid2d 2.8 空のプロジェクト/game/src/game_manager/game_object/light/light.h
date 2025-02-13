#pragma once
#include "..\..\..\utility\utility.h"
class CLight
{
public:
	CLight();
	~CLight();

	enum class LIGHT_TYPE
	{
	   DIRECTIONAL,
	   SPOT,
	   POINT
	};
	/*!
	*  @brief      初期化
	*/
	void Initialize(const CTransform& transform, const CVector3& direction, const COLOR_F& color, float intensity, LIGHT_TYPE light_type);

	/*!
	*  @brief      更新
	*/
	void Update();

	/*!
	*  @brief      描画
	*/
	void Draw();


	/*!
	*  @brief      解放
	*/
	void Finalize();

	/*!
	 *  @brief      ライトの向きを設定
	 *
	 *  @param[in]  direction     ライトの向き
	 */
	void        SetDirection(const CVector3& direction);

	/*!
	 *  @brief      ライトの範囲を設定
	 *
	 *  @param[in]  range     ライトの範囲
	 */
	void        SetRange(float range);

private:
	
	static const float m_max_atten2;
	CTransform		m_Transform;
	CVector3		m_Direction;
	COLOR_F			m_Color;
	float			m_Intensity;
	LIGHT_TYPE		m_LightType;
	int				m_Handle;
	float			m_Range;
	float			m_OutAngle;
	float			m_InAngle;
	float			m_Atten0;
	float			m_Atten1;
	float			m_Atten2;

};