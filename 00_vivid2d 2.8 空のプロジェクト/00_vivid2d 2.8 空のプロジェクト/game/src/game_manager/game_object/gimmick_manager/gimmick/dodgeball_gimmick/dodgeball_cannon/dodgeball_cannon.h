#pragma once
#include "../../../../model_manager/model/model.h"

enum class CANNON_STATE
{
    SPAWN,
    MOVE,
    STOP,
};

enum class CANNON_ROTATE
{
    RIGHT_GO,
    RIGHT_RETURN,
    LEFT_GO,
    LEFT_RETURN,
};

class CDodgeBallCannon
{
public:
	CDodgeBallCannon();
	~CDodgeBallCannon();

    /*!
     *  @brief      ������
     *
     */
    void    Initialize(CVector3 Pos, CVector3 Rot);

    /*!
     *  @brief      �X�V
     */
    void    Update(void);

    /*!
     *  @brief      �`��
     */
    void    Draw(void);

    /*!
     *  @brief      ���
     */
    void    Finalize(void);

    //�e����
    void    Shot(void);

private:
	CModel			    m_Model;
	CTransform		    m_Transform;
    CTransform          m_SetTransform;
    CANNON_STATE        m_NowState;
    int                 m_SpawnTimer;
    CANNON_ROTATE       m_NowRotate;
    int                 m_MinRotateTime;
    int                 m_RotateTimer;

    static const std::string    m_file_name;
    static const CVector3       m_spawn_pos;
    static const int            m_spawn_time;
    static const float          m_max_rotate_angle;
    static const int            m_rotate_time;
};