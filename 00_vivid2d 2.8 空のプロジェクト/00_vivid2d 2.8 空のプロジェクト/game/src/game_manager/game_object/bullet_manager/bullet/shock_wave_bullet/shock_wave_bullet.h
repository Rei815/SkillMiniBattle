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
     */
     void    Initialize(UNIT_CATEGORY category, const CVector3& position, const CVector3& direction) override;

    /*!
     *  @brief      �X�V
     */
    void    Update();
private:

    static const float	        m_max_speed;        //!< �ō����x
    static const float	        m_spread_speed;     //!< �L���鑬�x
    static const float	        m_height;           //!< ����̍���
    static const float          m_life_time;        //!< ��������
    static const float			m_acceleration;     //!< �����x
    static const float          m_scale;            //!< �傫��
    static const float          m_power;            //!< ��΂�����

    float m_SpreadSpeed;    //!< �L���鑬�x
    float m_CurrentScale;   //!< ���݂̃X�P�[����ێ�����
};