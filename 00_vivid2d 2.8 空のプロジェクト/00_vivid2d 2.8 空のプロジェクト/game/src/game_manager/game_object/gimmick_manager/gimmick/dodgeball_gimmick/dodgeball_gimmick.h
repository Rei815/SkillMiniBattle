
#pragma once
#include "..\gimmick.h"

enum class CANNON_DIRECTION
{
    UP,
    DOWN,
    RIGHT,
    LEFT,
    
    MAX,
};

class CDodgeBallGimmick : public CGimmick
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     */
    CDodgeBallGimmick();

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CDodgeBallGimmick(void);

    /*!
     *  @brief      ������
     *
     */
    void    Initialize();

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

private:
    CANNON_DIRECTION NextCannnonDir;
    static const int m_cannnon_count;
    static const int m_cannnon_spawn_time;

    int m_CannonSpawnTimer;

};
