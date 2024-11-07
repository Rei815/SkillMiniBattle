#pragma once
#include "vivid.h"
#include "..\..\mathematics\mathematics.h"
#include "..\..\utility\utility.h"
class CPlane
{
public:
	CPlane();
	~CPlane();

	void SetUp();
	void SetUp(const std::string fileName);


	void Update();

	void Draw();
	void Finalize();

	void SetScale(const CVector3& scale);
	void SetPosition(const CVector3& position);
	void SetRotation(const CVector3& rotation);
	//void Draw3DRot(int handle, const CVector3& position, int width, int height, const CVector3& rot);
	//void Draw3DRot(int handle, const CVector3& position, int width, int height, const CVector3& rot);
private:
	static const unsigned short m_index[];
	CTransform		m_Transform;
	std::string		m_FileName;
	int				m_Handle;
	DxLib::COLOR_U8 m_Color;
	DxLib::VERTEX3D m_Vertices[4];
	CMatrix			m_TransMat;
	CMatrix			m_RotMat;
	CMatrix			m_MulMat;

};