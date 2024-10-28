#pragma once
#include "..\gimmick.h"
#include "..\..\..\launcher\launcher.h"

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
    void    Initialize(IObject* object);

    void    Initialize(IObject* object, float time);

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

    CANNON_STATE    GetNowState();

    bool            GetShotFlag();

private:

    CTransform          m_SetTransform;
    CANNON_STATE        m_NowState;
    CANNON_ROTATE       m_NowRotate;
    CShot*              m_Shot;

    static const std::string    m_file_name;
    static const CVector3       m_spawn_pos;
    static const float          m_spawn_time;
    static const float          m_max_rotate_angle;
    static const float          m_rotate_time;
    static const float          m_min_rotate_time;
};
