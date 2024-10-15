
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
     *  @brief      コンストラクタ
     *
     */
    CDodgeBallGimmick();

    /*!
     *  @brief      デストラクタ
     */
    ~CDodgeBallGimmick(void);

    /*!
     *  @brief      初期化
     *
     */
    void    Initialize();

    /*!
     *  @brief      更新
     */
    void    Update(void);

    /*!
     *  @brief      描画
     */
    void    Draw(void);

    /*!
     *  @brief      解放
     */
    void    Finalize(void);

private:
    CANNON_DIRECTION NextCannnonDir;
    static const int m_cannnon_count;
    static const int m_cannnon_spawn_time;

    int m_CannonSpawnTimer;

};
