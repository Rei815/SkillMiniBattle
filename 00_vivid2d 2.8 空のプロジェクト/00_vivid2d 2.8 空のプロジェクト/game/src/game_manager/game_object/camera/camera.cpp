#include "camera.h"
#include "../unit_manager/unit_manager.h"
#include "vivid.h"
#include <EffekseerForDXLib.h>      // effekseerライブラリの読み込み

const float                 CCamera::m_lerp_speed = 0.1f;
const float                 CCamera::m_near = 100.0f;
const float                 CCamera::m_far = 200000.0f;
const float                 CCamera::m_fov = 60.0f;
const int                   CCamera::m_shake_interval = 3;                  //揺れの間隔
const int                   CCamera::m_shake_max_num = 5;                   //揺れる回数
const float                 CCamera::m_shake_value = 5.0f;                  //揺れの大きさ
const CVector3              CCamera::m_initial_position = CVector3();       //初期位置
const CVector3              CCamera::m_initial_direction = CVector3();      //初期の向き

CCamera& CCamera::GetInstance(void)
{
    static CCamera instance;

    return instance;
}


/*!
 *  @brief      カメラの初期化 
 */
void CCamera::Initialize()
{
    m_Position.x = 0.0f;
    m_Position.y = 400.0f;
    m_Position.z = -1000.0f;

    SetCameraNearFar(m_near, m_far);

    m_Direction = CVector3(0,-0.5,1);

    SetCameraPositionAndTarget_UpVecY(m_Position, m_Position + m_Direction);

}

/*!
 *  @brief      カメラの更新
 */
void CCamera::Update()
{
    //カメラを揺らす処理
    _Shake();

    // カメラの位置と注視点をセット、注視点は向いている向き
    SetCameraPositionAndTarget_UpVecY(m_Position + m_ShakeVector, m_Position + m_Direction + m_ShakeVector);

    // 遠近法のセットアップ( ラジアン値に変換しています )
    SetupCamera_Perspective(DEG_TO_RAD(m_Fov));

    Effekseer_Sync3DSetting();

}


/*
 *  解放
 */
void
CCamera::Finalize(void)
{
}

void CCamera::Follow(const CVector3& position,const CVector3& offset)
{
    m_Position = CVector3::Lerp(m_Position, position + offset, m_lerp_speed);
}

void CCamera::SetPosition(const CVector3& position)
{
    m_Position = position;
    // カメラの位置と注視点をセット、注視点は向いている向き
    SetCameraPositionAndTarget_UpVecY(m_Position + m_ShakeVector, m_Position + m_Direction + m_ShakeVector);

}

void CCamera::SetDirection(const CVector3& direction)
{
    m_Direction = direction;
    // カメラの位置と注視点をセット、注視点は向いている向き
    SetCameraPositionAndTarget_UpVecY(m_Position + m_ShakeVector, m_Position + m_Direction + m_ShakeVector);

}

CVector3 CCamera::GetPosition()
{
    return m_Position;
}

float CCamera::GetNear()
{
    return m_near;
}

float CCamera::GetFar()
{
    return m_far;
}

void CCamera::Shake()
{
    m_ShakeFlag = true;


}

void CCamera::_Shake()
{
    if (!m_ShakeFlag)
        return;

    if (++m_ShakeTimer > m_shake_interval)
    {
        m_ShakeVector = CVector3::ZERO;

        // カメラの位置と注視点をセット、注視点は向いている向き
        SetCameraPositionAndTarget_UpVecY(m_Position + m_ShakeVector, m_Position + m_Direction + m_ShakeVector);

        m_ShakeTimer = 0;
        m_ShakeVector = CVector3::DeviationToDirection(m_ShakeVector, m_shake_value);

        if (++m_ShakeCount > m_shake_max_num)
        {
            m_ShakeCount = 0;
            m_ShakeFlag = false;
        }
    }
}

/*!
 *  @brief      コンストラクタ
 */
CCamera::CCamera()
	: m_Position()
    , m_Direction()
    , m_Fov(m_fov)
    , m_Offset()
    , m_ShakeCount()
    , m_ShakeFlag()
    , m_ShakeTimer()
    , m_ShakeVector()
{
}

/*
 *  コピーコンストラクタ
 */
CCamera::
CCamera(const CCamera& rhs)
{
    (void)rhs;
}

/*
 *  デストラクタ
 */
CCamera::
~CCamera(void)
{
}

/*
 *  代入演算子
 */
CCamera&
CCamera::
operator=(const CCamera& rhs)
{
    (void)rhs;

    return *this;
}
