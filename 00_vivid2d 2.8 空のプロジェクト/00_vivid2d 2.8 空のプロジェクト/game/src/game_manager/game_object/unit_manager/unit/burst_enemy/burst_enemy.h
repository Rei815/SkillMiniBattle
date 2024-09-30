#pragma once

#include "..\..\..\..\..\mathematics\mathematics.h"
#include "..\unit.h"
#include "../../../model_manager/model/model.h"
#include "../../../bullet_manager/bullet/bullet.h"

class CBurstEnemy : public IUnit
{
public:

    CBurstEnemy();

    ~CBurstEnemy();

    /*!
     *  @brief      ������
     *
     *  @param[in]  position    �ʒu
     *  @param[in]  moveID      ������ID
     *  @param[in]  aimFlag     �_�����ǂ���
     */
    virtual void    Initialize(const CVector3& position, MOVE_ID moveID, bool aimFlag);

    /*!
     *  @brief      �X�V
     */
    void        Update(void);

    /*!
     *  @brief      �`��
     */
    void        Draw(void);

    /*!
     *  @brief      ���
     */
    void        Finalize(void);
private:

    enum BURST_STATE
    {
        WAIT,
        FIRE,
    };
    /*!
     *  @brief      �U��
     */
    void        Attack(void);

    /*!
     *  @brief      �ړ�
     */
    void        Move(void);

    /*!
     *  @brief      ���S
     */
    void        Dead(void);

    static const CVector3           m_StartValue;           //!< �����ʒu
    static const float              m_max_life;             //!< �ő僉�C�t
    static const float              m_move_speed;           //!< �ړ����x
    static const float              m_radius;               //!< ���a

    CVector3                        m_Accelerator;          //!< �����x
};