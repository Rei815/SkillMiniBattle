#pragma once
#include "..\bullet.h"
#include "..\..\..\effect_manager\effect\effect.h"
class CCannonBullet : public IBullet
{
public:
	CCannonBullet();
	~CCannonBullet() = default;
    /*!
     *  @brief      初期化
     *
     *  @param[in]  category        ユニット識別子
     *  @param[in]  bulletParameter パラメータ
     *  @param[in]  position        発射ID
     *  @param[in]  direction       向き
     */
    void    Initialize(FACTION_CATEGORY category, CShot::BulletParameters* bulletParameter, const CVector3& position, const CVector3& direction);

	/*!
	 *  @brief      更新
	 */
	void    Update();

private:
    static const std::string    m_file_name;        //!< 読み込むファイル名
    static const float	        m_max_speed;        //!< 最高速度
};