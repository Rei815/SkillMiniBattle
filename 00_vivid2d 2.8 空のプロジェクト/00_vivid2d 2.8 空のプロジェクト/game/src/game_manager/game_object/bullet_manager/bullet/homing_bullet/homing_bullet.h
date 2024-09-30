#pragma once
#include "..\bullet.h"

class CHomingBullet : public IBullet
{
public:
	CHomingBullet();
	~CHomingBullet() = default;
	/*!
	 *  @brief      ������
	 *
	 *  @param[in]  category        ���j�b�g���ʎq
	 *  @param[in]  position        �ʒu
	 *  @param[in]  direction       ����
	 *  @param[in]  launcherID      ����ID
	 *  @param[in]  colliderID      ����ID
	 */
	 void    Initialize(UNIT_CATEGORY category, CShot::BulletParameters* bulletParameter, const CVector3& position, const CVector3& direction);

	/*!
	 *  @brief      �X�V
	 */
	void    Update();

private:

	static const std::string    m_file_name;        //!< �ǂݍ��ރt�@�C����
	static const float	        m_max_speed;        //!< �ō����x

	static const int	m_max_homing_time;          //!< �z�[�~���O����ő厞��
	static const float	m_curvature_radius;			//!< �ȗ����a
	static const float	m_damping;					//!< ��C��R

	float				m_MaxCentripetalAccel;		//!< �ő�����x
	int					m_HomingTime;               //!< �z�[�~���O���鎞��
	float				m_Propulsion;				//!< ���i��
	float				m_Damping;					//!< ������
	int					m_StartHomingTime;			//!< �z�[�~���O�܂ł̎���
	int					m_DelayTimer;				//!< �x���^�C�}�[
};