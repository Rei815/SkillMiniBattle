#include "homing_bullet.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../launcher/launcher.h"

const std::string   CHomingBullet:: m_file_name = "data\\Models\\homing.mv1";
const int           CHomingBullet:: m_max_homing_time = 120;
const float         CHomingBullet:: m_curvature_radius = 250.0f;
const float         CHomingBullet:: m_damping = 1.0f;
const float         CHomingBullet:: m_max_speed = 30.0f;

/*
 *  �R���X�g���N�^
 */
CHomingBullet::CHomingBullet()
    : IBullet(m_file_name, COLLIDER_ID::SPHERE)
    , m_HomingTime(m_max_homing_time)
    , m_Propulsion(0.0f)
    , m_Damping(0)
    , m_StartHomingTime(0)
    , m_DelayTimer(0)
{

}

/*
 *  ������
 */
void CHomingBullet::Initialize(UNIT_CATEGORY category, CShot::BulletParameters* bulletParameter, const CVector3& position, const CVector3& direction)
{
    IBullet::Initialize(category, bulletParameter, position, direction);

    m_Speed = bulletParameter->speed;
    m_Direction = direction;
    m_HomingTime = m_max_homing_time;
    m_Accleration = bulletParameter->acceleration;
    m_StartHomingTime = bulletParameter->homingDelayTime;
    // ����v�A���ar�ŉ~��`�����A���̌��S�͂�v^2/r�B������v�Z���Ă����B
    //m_MaxCentripetalAccel = m_Speed * m_Speed / m_curvature_radius;

    // �I�[���x��m_Speed�ɂȂ�accel�����߂�
    // v = a / k������a=v*k
    m_Propulsion = m_Speed * m_damping;

}

void CHomingBullet::Update()
{
    //�z�[�~���O�ɂȂ�����F�ύX
    if(m_DelayTimer == m_StartHomingTime)
        MV1SetMaterialDifColor(m_Model.GetModelHandle(), 0, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
    ++m_DelayTimer;

    // �z�[�~���O�J�n���Ԃ��߂���������J�n
    if (m_DelayTimer > m_StartHomingTime)
    {
        m_StartHomingTime = 0;
        m_Speed += m_Accleration;    // ���X�ɉ���������
    }

    if (m_StartHomingTime <= 0)
    {
        //�z�[�~���O����
        if (--m_HomingTime > 0)
        {

            //�e����ΏۂɌ����Ẵx�N�g�������߂�
            IUnit* player = CUnitManager::GetInstance().GetPlayer(UNIT_ID::PLAYER1);

            if (!player) return;
            //�e����ΏۂɌ������x�N�g��
            CVector3 toTarget = (player->GetPosition() - m_Transform.position).Normalize();
            CVector3 vn = m_Velocity.Normalize();

            //���x�x�N�g���ƑΏۂɌ������x�N�g���̊O��(��)
            CVector3 cross = CVector3::Cross(toTarget, vn);

            //�ˉe(�G�Ɍ������x�N�g���𑬓x�x�N�g���Ɏˉe)
            float dot = CVector3::Dot(toTarget, vn);

            //���x��G�����ɋȂ���x�N�g�����v�Z
            CVector3 centripetalAccel = toTarget - (vn * dot);

            //�Ȃ���x�N�g���̒���
            float centripetalAccelMagnitude = centripetalAccel.Length();

            //centripetalAccel�̒���(magnitude)��1�ȏ�Ȃ琳�K��
            if (centripetalAccelMagnitude > 1.0f)
                centripetalAccel /= centripetalAccelMagnitude;

            //�����̒���(������maxCentripetalAccel�ȉ��Ȃ炻�̂܂܁A�ȏ�Ȃ璷����maxCentripetalAccel�ɂ���)   �������ς�邱�Ƃ�����̂ł����Ōv�Z
            CVector3 force = centripetalAccel * (m_Speed * m_Speed / m_curvature_radius);

            // ���i��
            force += vn * m_Speed * m_damping;

            // ��C��R
            force -= m_Velocity * m_damping;

            // ���x�ϕ�
            //�v���C���[��ʂ�߂��Ă���Ȃ�z�[�~���O���Ȃ�
            if (player->GetPosition().z < m_Transform.position.z)
            m_Velocity += force;

            //�i��ł�������Ɍ��������킹��
            MV1SetRotationZYAxis(m_Model.GetModelHandle(), m_Velocity, VGet(0.0f, 1.0f, 0.0f), 0.0f);
        }
    }
    else
        m_Velocity = m_Direction * m_Speed;

    // �ō����x����
    if (m_Speed > m_max_speed)
        m_Speed = m_max_speed;
    IBullet::Update();
}