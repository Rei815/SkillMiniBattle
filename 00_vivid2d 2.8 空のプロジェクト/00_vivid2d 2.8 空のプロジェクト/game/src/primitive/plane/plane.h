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
	void _Draw();
	void Draw(const CMatrix& mat);
	void Finalize();

	void				SetTransform(const CTransform& transform);
	CTransform			GetTransform();
	CTransform*			GetTransformPointer();
	struct MATRICES
	{
		CMatrix			m_TransMat;
		CMatrix			m_RotMat;
		CMatrix			m_MulMat;
	};

	CPlane::MATRICES			GetMatrices();

	void				SetMatrix(const CMatrix& matrix);
	void				SetScale(const CVector3& scale);
	void				SetPosition(const CVector3& position);
	void				SetRotation(const CVector3& rotation);
	void				SetVertices();
	void				SetVertices(const CMatrix& matrix);
	void				Translation();
	void				Rotation();
private:

	static const unsigned short m_index[];
	CTransform			m_Transform;
	std::string			m_FileName;
	int					m_Handle;
	DxLib::COLOR_U8		m_Color;
	DxLib::VERTEX3D		m_Vertices[4];
	MATRICES			m_Matrices;

	/**/
	int			m_Width;
	int			m_Height;
	CVector3	m_Normal;

};