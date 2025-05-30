#pragma once
#include "..\..\mathematics\mathematics.h"

class CTransform
{
public:

    CVector3 position;  //!< �ʒu
    CVector3 rotation;  //!< ��]
    CVector3 scale;     //!< �傫��

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
    
    /*!
    *  @brief       �w��̎��𒆐S�ɉ�](�t���[��)
    *
    *  @param[in]   handle       ���f���̃n���h��
    *  @param[in]   frameIndex   �t���[���̔ԍ�
    *  @param[in]   point        ���̍��W
    *  @param[in]   axis         ��]��
    *  @param[in]   angle        �p�x
    *
    */
    void            RotateAround(int handle, int frameIndex, const CVector3& point, const CVector3& axis, float angle);

    /*!
    *  @brief       �w��̎��𒆐S�ɉ�]
    *
    *  @param[in]   point        ���̍��W
    *  @param[in]   axis         ��]��
    *  @param[in]   angle        �p�x
    *  @param[in]   initPos      �����ʒu
    *
    */
    void            RotateAround(const CVector3& point, const CVector3& axis, float angle, const CVector3& initPos);
    /*!
    *  @brief       �w��̎��𒆐S�ɉ�]
    *
    *  @param[in]   point        ���̍��W
    *  @param[in]   axis         ��]��
    *  @param[in]   speed        ��]���x
    *
    */
    void            RotateAround(const CVector3& point, const CVector3& axis, float rotateSpeed);
    /*!
    *  @brief       �w��̎��𒆐S�ɉ�](�s��)
    *
    *  @param[in]   point        ���̍��W
    *  @param[in]   axis         ��]��
    *  @param[in]   speed        ��]���x
    *  @return      �s��N���X
    *
    */
    CMatrix         GetRotateAroundMatrix(const CVector3& point, const CVector3& axis, CMatrix& mulMat, CMatrix& tranMat, CMatrix& rotMat, float rotateSpeed, float angle);

    /*!
    *  @brief       �e�̃g�����X�t�H�[����ݒ�
    *
    *  @param[in]   transform        �e�̃g�����X�t�H�[��
    *
    */
    void            SetParent(CTransform* transform);

private:
    CVector3 GetRotateVector(CVector3 vector);

    CVector3 center;
    CVector3 angle;
    CVector3 scaling;
    CTransform* m_Parent;
};