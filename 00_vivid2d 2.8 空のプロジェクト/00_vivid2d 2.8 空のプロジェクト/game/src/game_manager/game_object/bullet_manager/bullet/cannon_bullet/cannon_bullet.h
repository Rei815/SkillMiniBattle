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
     *  @param[in]  position        位置
     *  @param[in]  direction       向き
     *  @param[in]  launcherID      発射ID
     *  @param[in]  colliderID      判定ID
     */
    void    Initialize(UNIT_CATEGORY category, CShot::BulletParameters* bulletParameter, const CVector3& position, const CVector3& direction);

	/*!
	 *  @brief      更新
	 */
	void    Update();

    /*!
     *  @brief      解放
     */
    void    Finalize(void);

private:
    static const std::string    m_file_name;        //!< 読み込むファイル名
    static const float	        m_max_speed;        //!< 最高速度
    static const float	        m_effect2_speed;    //!< エフェクトの表示位置の移動速度
    IEffect*                     m_Effect;
    IEffect*                     m_Effect2;
};