#pragma once
#include "..\bullet.h"
#include "..\..\..\effect_manager\effect\effect.h"
class CCannonBullet : public IBullet
{
public:
	CCannonBullet();
	~CCannonBullet() = default;
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

    /*!
     *  @brief      ���
     */
    void    Finalize(void);

private:
    static const std::string    m_file_name;        //!< �ǂݍ��ރt�@�C����
    static const float	        m_max_speed;        //!< �ō����x
};