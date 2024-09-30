#pragma once
#include "..\..\bullet_manager\bullet\bullet_id.h"
#include "..\..\unit_manager\unit\unit_id.h"
#include "..\..\..\..\mathematics\mathematics.h"
class CShot
{
public:

    /*!
     *  @brief      ƒpƒ‰ƒ[ƒ^\‘¢‘Ì
     *  @param bullet_interval  ”­Ë‘¬“x
     *  @param fire_interval    UŒ‚‘¬“x
     *  @param capacity         ‘•“U”
     *  @param bullets          ”­Ë”
     *  @param speed            ‘¬“x
     *  @param deviation        ƒuƒŒ
     *  @param radius           ”¼Œa
     *  @param damage           UŒ‚—Í
     *  @param homingDelayTime  —U“±’x‰„ŠÔ
     *  @param acceleration     ‰Á‘¬—Í
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
     *  @brief      ‰Šú‰»
     *
     */
    virtual void    Initialize();

    /*!
     *  @brief      XV
     */
    virtual void    Update(void);

    /*!
     *  @brief      ‰ğ•ú
     */
    virtual void    Finalize(void);

    /*!
     *  @brief      ”­Ë
     */
    virtual void    Shot(UNIT_CATEGORY unitCategory, CVector3& position, const CVector3& direction);

    /*!
     *  @brief      ’e”’Ç‰Á
     */
    void            AddShot();

    /*!
     *  @brief      ”­Ë”’Ç‰Á
     */
    void            AddBullet();

    /*!
     *  @brief      ”­Ë”æ“¾
     * @return      ”­Ë”
     */
    int            GetBullets();

    /*!
     *  @brief      ‘•“U”æ“¾
     * @return      ‘•“U”
     */
    int            GetCapacity();
protected:

    void            Interval();
    static const BulletParameters       m_bullet_parameters;
    BulletParameters*                   m_BulletParameters;
    int                                 m_BulletInterval;
    int                                 m_FireInterval;
    bool                                m_ShotFlag;
    int                                 m_ShotCount;
    CVector3*                           m_Position;
    CVector3                            m_Direction;
    UNIT_CATEGORY                       m_UnitCategory;
};