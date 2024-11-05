#include "polygon.h"

void polygon::Draw3DRot(int handle, const CVector3& position, int width, int height, const CVector3& rot)
{
	DxLib::VERTEX3D vertices[] = {
	{VGet(-width / 2,	-height / 2,	0.0f), {0.0f, 0.0f, 1.0f}, DxLib::GetColorU8(255, 255, 255, 255), DxLib::GetColorU8(255, 255, 255, 255), 0.0f, 1.0f, 0.0f, 0.0f },
	{VGet(width / 2,	-height / 2,	0.0f), {0.0f, 0.0f, 1.0f}, DxLib::GetColorU8(255, 255, 255, 255), DxLib::GetColorU8(255, 255, 255, 255), 1.0f, 1.0f, 0.0f, 0.0f },
	{VGet(width / 2,	 height / 2,	0.0f), {0.0f, 0.0f, 1.0f}, DxLib::GetColorU8(255, 255, 255, 255), DxLib::GetColorU8(255, 255, 255, 255), 1.0f, 0.0f, 0.0f, 0.0f },
	{VGet(-width / 2,	 height / 2,	0.0f), {0.0f, 0.0f, 1.0f}, DxLib::GetColorU8(255, 255, 255, 255), DxLib::GetColorU8(255, 255, 255, 255), 0.0f, 0.0f, 0.0f, 0.0f },
	};

	unsigned short index[] = { 0,1,3,3,1,2 };

	MATRIX transMat, rotMat, mulMat;

	CreateTranslationMatrix(&transMat, position.x, position.y, position.z);
	CreateRotationYXZMatrix(&rotMat, rot.x, rot.y, rot.z);

	// �P�ʍs��
	CreateIdentityMatrix(&mulMat);
	// ��]������ 
	CreateMultiplyMatrix(&mulMat, &mulMat, &rotMat);
	// �ړ�������
	CreateMultiplyMatrix(&mulMat, &mulMat, &transMat);

	// �e���_�ɍs���K�p
	for (int i = 0; i < 4; i++)
	{
		VectorTransform(&vertices[i].pos, &vertices[i].pos, &mulMat);
	}

	DrawPolygonIndexed3D(vertices, 4, index, 2, handle, TRUE);

}
