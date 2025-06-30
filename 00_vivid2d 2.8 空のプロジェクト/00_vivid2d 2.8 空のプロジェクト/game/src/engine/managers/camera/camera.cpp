#include "camera.h"
#include "../unit_manager/unit_manager.h"
#include "vivid.h"
#include <EffekseerForDXLib.h>      // effekseer���C�u�����̓ǂݍ���

const float                 CCamera::m_lerp_speed = 0.1f;       //�J�����̓����̑���
const float                 CCamera::m_near = 100.0f;           //Near�N���b�v
const float                 CCamera::m_far = 200000.0f;         //Far�N���b�v
const float                 CCamera::m_fov = 60.0f;             //Fov�N���b�v
const float                 CCamera::m_shake_interval = 0.04;   //�h��̊Ԋu
const int                   CCamera::m_shake_max_num = 5;       //�ő�̗h����
const float                 CCamera::m_shake_value = 5.0f;      //�h��̑傫��
const CVector3              CCamera::m_position = CVector3(0, 400, -1000);  //�����ʒu
const CVector3              CCamera::m_direction = CVector3::FORWARD;       //�����̌���

CCamera& CCamera::GetInstance(void)
{
    static CCamera instance;

    return instance;
}


/*!
 *  @brief      �J�����̏����� 
 */
void CCamera::Initialize()
{
    SetCameraNearFar(m_near, m_far);

    SetCameraPositionAndTarget_UpVecY(m_Position, m_Position + m_Direction);

}

/*!
 *  @brief      �J�����̍X�V
 */
void CCamera::Update()
{
    //�J������h�炷����
    _Shake();

    // �J�����̈ʒu�ƒ����_���Z�b�g�A�����_�͌����Ă������
    SetCameraPositionAndTarget_UpVecY(m_Position + m_ShakeVector, m_Position + m_Direction + m_ShakeVector);

    // ���ߖ@�̃Z�b�g�A�b�v( ���W�A���l�ɕϊ����Ă��܂� )
    SetupCamera_Perspective(DEG_TO_RAD(m_Fov));

    Effekseer_Sync3DSetting();

}


/*
 *  ���
 */
void
CCamera::Finalize(void)
{
}

void CCamera::Follow(const CVector3& position,const CVector3& offset)
{
    m_Position = CVector3::Lerp(m_Position, position + offset, m_lerp_speed);
}

void CCamera::SetPosition(const CVector3& position)
{
    m_Position = position;
    // �J�����̈ʒu�ƒ����_���Z�b�g�A�����_�͌����Ă������
    SetCameraPositionAndTarget_UpVecY(m_Position + m_ShakeVector, m_Position + m_Direction + m_ShakeVector);

}

void CCamera::SetDirection(const CVector3& direction)
{
    m_Direction = direction;
    // �J�����̈ʒu�ƒ����_���Z�b�g�A�����_�͌����Ă������
    SetCameraPositionAndTarget_UpVecY(m_Position + m_ShakeVector, m_Position + m_Direction + m_ShakeVector);

}

CVector3 CCamera::GetPosition()
{
    return m_Position;
}

float CCamera::GetNear()
{
    return m_near;
}

float CCamera::GetFar()
{
    return m_far;
}

void CCamera::Shake()
{
    m_ShakeFlag = true;

    m_ShakeTimer.Reset();
}

void CCamera::_Shake()
{
    if (!m_ShakeFlag)
        return;

    m_ShakeTimer.Update();
    if (!m_ShakeTimer.Finished())
    {

        m_ShakeVector = CVector3::ZERO;

        // �J�����̈ʒu�ƒ����_���Z�b�g�A�����_�͌����Ă������
        SetCameraPositionAndTarget_UpVecY(m_Position + m_ShakeVector, m_Position + m_Direction + m_ShakeVector);

        m_ShakeTimer.Reset();
        m_ShakeVector = CVector3::DeviationToDirection(m_ShakeVector, m_shake_value);
        ++m_ShakeCount;
    }
    if(m_ShakeCount > m_shake_max_num)
        m_ShakeFlag = false;
}

/*!
 *  @brief      �R���X�g���N�^
 */
CCamera::CCamera()
	: m_Position(m_position)
    , m_Direction(m_direction)
    , m_Fov(m_fov)
    , m_Offset()
    , m_ShakeCount(m_shake_max_num)
    , m_ShakeFlag(false)
    , m_ShakeTimer(m_shake_interval)
    , m_ShakeVector(CVector3::ZERO)
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
CCamera::
CCamera(const CCamera& rhs)
{
    (void)rhs;
}

/*
 *  �f�X�g���N�^
 */
CCamera::
~CCamera(void)
{
}

/*
 *  ������Z�q
 */
CCamera&
CCamera::
operator=(const CCamera& rhs)
{
    (void)rhs;

    return *this;
}
