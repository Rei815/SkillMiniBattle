#pragma once
#include "..\..\bullet_manager\bullet\bullet_id.h"
#include "..\..\..\mathematics\vector\vector3\vector3.h"
#include "..\..\..\core\game_object\game_types.h"
class CShot
{
public:

    /*!
     *  @brief      �p�����[�^�\����
     *  @param bullet_interval  ���ˑ��x
     *  @param fire_interval    �U�����x
     *  @param capacity         ���U��
     *  @param bullets          ���ː�
     *  @param speed            ���x
     *  @param deviation        �u��
     *  @param radius           ���a
     *  @param damage           �U����
     *  @param homingDelayTime  �U�����x������
     *  @param acceleration     ������
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
     *  @brief      ������
     *
     */
    virtual void    Initialize();

    /*!
     *  @brief      �X�V
     */
    virtual void    Update(void);

    /*!
     *  @brief      ���
     */
    virtual void    Finalize(void);

    /*!
     *  @brief      ����
     */
    virtual void    Shot(FACTION_CATEGORY unitCategory, CVector3& position, const CVector3& direction);

    /*!
     *  @brief      �e���ǉ�
     */
    void            AddShot();

    /*!
     *  @brief      ���ː��ǉ�
     */
    void            AddBullet();

    /*!
     *  @brief      ���ː��擾
     * @return      ���ː�
     */
    int            GetBullets();

    /*!
     *  @brief      ���U���擾
     * @return      ���U��
     */
    int            GetCapacity();

    /*!
    *  @brief      ���˃t���O�擾
    * @return      ���˃t���O
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
    FACTION_CATEGORY                    m_Category;
};