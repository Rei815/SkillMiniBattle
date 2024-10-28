#pragma once
#include "..\..\mathematics\mathematics.h"
class CTransform
{
public:

    CVector3 position;
    CVector3 rotation;
    CVector3 scale;

    /*
    CVector3 forward;
    CVector3 right;
    CVector3 up;
    */

    /*!
     *  @brief  �R���X�g���N�^
     */
    CTransform();
    /*!
     *  @brief  �R���X�g���N�^
     */
    CTransform(const CVector3& pos);

    /*!
     *  @brief  �R���X�g���N�^
     */
    CTransform(const CVector3& pos, const CVector3& rot);

    /*!
     *  @brief  �f�X�g���N�^
     */
    ~CTransform() = default;

    /*!
    *  @brief      ������Z�q�̃I�[�o�[���[�h
    *
    *  @param[in]  t   �g�����X�t�H�[���N���X
    *
    *  @return     �g�����X�t�H�[���N���X
    */
    CTransform& operator=(const CTransform& t);

    CVector3 GetForwardVector(void);
    CVector3 GetRightVector(void);
    CVector3 GetUpVector(void);

    CVector3 GetRadianRotation(void);

private:
    CVector3 GetRotateVector(CVector3 vector);

    CVector3 center;
    CVector3 angle;
    CVector3 scaling;

};