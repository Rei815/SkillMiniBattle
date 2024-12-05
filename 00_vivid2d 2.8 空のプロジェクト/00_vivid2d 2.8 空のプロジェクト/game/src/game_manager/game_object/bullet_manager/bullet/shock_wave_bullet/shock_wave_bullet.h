#pragma once
#include "..\bullet.h"

class CShockWaveBullet : public IBullet
{
public:
	CShockWaveBullet();
	~CShockWaveBullet() = default;
    /*!
     *  @brief      ������
     *
     *  @param[in]  category        ���j�b�g���ʎq
     *  @param[in]  position        �ʒu
     *  @param[in]  direction       ����
     *  @param[in]  launcherID      ����ID
     *  @param[in]  colliderID      ����ID
     */
     void    Initialize(UNIT_CATEGORY category, const CVector3& position, const CVector3& direction);

    /*!
     *  @brief      �X�V
     */
    void    Update();

    /*!
     *  @brief      �X�V
     */
    void    Draw();
private:

    static const std::string    m_file_name;        //!< �ǂݍ��ރt�@�C����
    static const float	        m_max_speed;        //!< �ō����x
    static const float	        m_spread_speed;     //!< �L���鑬�x
    static const float	        m_height;           //!< ����̍���
    static const int            m_life_time;        //!< ��������
    static const float			m_acceleration;     //!< �����x
    static const float          m_scale;            //!< �傫��
    static const float          m_power;            //!< ��΂�����
};