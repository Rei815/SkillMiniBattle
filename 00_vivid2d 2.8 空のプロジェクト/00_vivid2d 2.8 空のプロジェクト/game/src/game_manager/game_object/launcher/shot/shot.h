#pragma once
#include "..\..\bullet_manager\bullet\bullet_id.h"
#include "..\..\unit_manager\unit\unit_id.h"
#include "..\..\..\..\mathematics\mathematics.h"
class CShot
{
public:

    /*!
     *  @brief      パラメータ構造体
     *  @param bullet_interval  発射速度
     *  @param fire_interval    攻撃速度
     *  @param capacity         装填数
     *  @param bullets          発射数
     *  @param speed            速度
     *  @param deviation        ブレ
     *  @param radius           半径
     *  @param damage           攻撃力
     *  @param homingDelayTime  誘導時遅延時間
     *  @param acceleration     加速力
     */
    struct BulletParameters
    {
        BULLET_ID   bulletID;
        int         bulletInterval;
        int         fireInterval;
        int         capacity;
        int         bullets;
        float       speed;
        float       deviation;
        float       radius;
        float       damage;
        int         homingDelayTime;
        float       acceleration;
    };

    CShot();
	CShot(BulletParameters bulletParameters);
	~CShot();

    /*!
     *  @brief      初期化
     *
     */
    virtual void    Initialize();

    /*!
     *  @brief      更新
     */
    virtual void    Update(void);

    /*!
     *  @brief      解放
     */
    virtual void    Finalize(void);

    /*!
     *  @brief      発射
     */
    virtual void    Shot(UNIT_CATEGORY unitCategory, CVector3& position, const CVector3& direction);

    /*!
     *  @brief      弾数追加
     */
    void            AddShot();

    /*!
     *  @brief      発射数追加
     */
    void            AddBullet();

    /*!
     *  @brief      発射数取得
     * @return      発射数
     */
    int            GetBullets();

    /*!
     *  @brief      装填数取得
     * @return      装填数
     */
    int            GetCapacity();

    /*!
    *  @brief      発射フラグ取得
    * @return      発射フラグ
    */
    bool            GetShotFlag();

protected:

    void            Interval();
    static const BulletParameters       m_bullet_parameters;
    BulletParameters*                   m_BulletParameters;
    int                                 m_BulletInterval;
    int                                 m_FireInterval;
    bool                                m_ShotFlag;
    int                                 m_ShotCount;
    CVector3                            m_Position;
    CVector3                            m_Direction;
    UNIT_CATEGORY                       m_UnitCategory;
};