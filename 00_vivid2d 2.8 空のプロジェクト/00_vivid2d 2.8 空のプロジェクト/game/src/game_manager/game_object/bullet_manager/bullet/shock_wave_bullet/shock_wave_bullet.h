#pragma once
#include "..\bullet.h"

class CShockWaveBullet : public IBullet
{
public:
	CShockWaveBullet();
	~CShockWaveBullet() = default;
    /*!
     *  @brief      初期化
     *
     *  @param[in]  category        ユニット識別子
     *  @param[in]  position        位置
     *  @param[in]  direction       向き
     *  @param[in]  launcherID      発射ID
     *  @param[in]  colliderID      判定ID
     */
     void    Initialize(UNIT_CATEGORY category, const CVector3& position, const CVector3& direction);

    /*!
     *  @brief      更新
     */
    void    Update();

    /*!
     *  @brief      更新
     */
    void    Draw();
private:

    static const std::string    m_file_name;        //!< 読み込むファイル名
    static const float	        m_max_speed;        //!< 最高速度
    static const float	        m_spread_speed;     //!< 広がる速度
    static const float	        m_height;           //!< 判定の高さ
    static const int            m_life_time;        //!< 持続時間
    static const float			m_acceleration;     //!< 加速度
    static const float          m_scale;            //!< 大きさ
    static const float          m_power;            //!< 飛ばす強さ
};