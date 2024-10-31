#include "homing_bullet.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../launcher/launcher.h"

const std::string   CHomingBullet:: m_file_name = "data\\Models\\homing.mv1";
const int           CHomingBullet:: m_max_homing_time = 120;
const float         CHomingBullet:: m_curvature_radius = 250.0f;
const float         CHomingBullet:: m_damping = 1.0f;
const float         CHomingBullet:: m_max_speed = 30.0f;

/*
 *  コンストラクタ
 */
CHomingBullet::CHomingBullet()
    : IBullet(m_file_name, COLLIDER_ID::SPHERE)
    , m_HomingTime(m_max_homing_time)
    , m_Propulsion(0.0f)
    , m_Damping(0)
    , m_StartHomingTime(0)
    , m_DelayTimer(0)
{

}

/*
 *  初期化
 */
void CHomingBullet::Initialize(UNIT_CATEGORY category, CShot::BulletParameters* bulletParameter, const CVector3& position, const CVector3& direction)
{
    IBullet::Initialize(category, bulletParameter, position, direction);

    m_Speed = bulletParameter->speed;
    m_Direction = direction;
    m_HomingTime = m_max_homing_time;
    m_Accleration = bulletParameter->acceleration;
    m_StartHomingTime = bulletParameter->homingDelayTime;
    // 速さv、半径rで円を描く時、その向心力はv^2/r。これを計算しておく。
    //m_MaxCentripetalAccel = m_Speed * m_Speed / m_curvature_radius;

    // 終端速度がm_Speedになるaccelを求める
    // v = a / kだからa=v*k
    m_Propulsion = m_Speed * m_damping;

}

void CHomingBullet::Update()
{
    //ホーミングになったら色変更
    if(m_DelayTimer == m_StartHomingTime)
        MV1SetMaterialDifColor(m_Model.GetModelHandle(), 0, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
    ++m_DelayTimer;

    // ホーミング開始時間を過ぎたら加速開始
    if (m_DelayTimer > m_StartHomingTime)
    {
        m_StartHomingTime = 0;
        m_Speed += m_Accleration;    // 徐々に加速させる
    }

    if (m_StartHomingTime <= 0)
    {
        //ホーミング時間
        if (--m_HomingTime > 0)
        {

            //弾から対象に向けてのベクトルを求める
            IUnit* player = CUnitManager::GetInstance().GetPlayer(UNIT_ID::PLAYER1);

            if (!player) return;
            //弾から対象に向かうベクトル
            CVector3 toTarget = (player->GetPosition() - m_Transform.position).Normalize();
            CVector3 vn = m_Velocity.Normalize();

            //速度ベクトルと対象に向かうベクトルの外積(軸)
            CVector3 cross = CVector3::Cross(toTarget, vn);

            //射影(敵に向かうベクトルを速度ベクトルに射影)
            float dot = CVector3::Dot(toTarget, vn);

            //速度を敵方向に曲げるベクトルを計算
            CVector3 centripetalAccel = toTarget - (vn * dot);

            //曲げるベクトルの長さ
            float centripetalAccelMagnitude = centripetalAccel.Length();

            //centripetalAccelの長さ(magnitude)が1以上なら正規化
            if (centripetalAccelMagnitude > 1.0f)
                centripetalAccel /= centripetalAccelMagnitude;

            //長さの調整(長さがmaxCentripetalAccel以下ならそのまま、以上なら長さをmaxCentripetalAccelにする)   速さが変わることがあるのでここで計算
            CVector3 force = centripetalAccel * (m_Speed * m_Speed / m_curvature_radius);

            // 推進力
            force += vn * m_Speed * m_damping;

            // 空気抵抗
            force -= m_Velocity * m_damping;

            // 速度積分
            //プレイヤーを通り過ぎているならホーミングしない
            if (player->GetPosition().z < m_Transform.position.z)
            m_Velocity += force;

            //進んでいる方向に向きを合わせる
            MV1SetRotationZYAxis(m_Model.GetModelHandle(), m_Velocity, VGet(0.0f, 1.0f, 0.0f), 0.0f);
        }
    }
    else
        m_Velocity = m_Direction * m_Speed;

    // 最高速度制限
    if (m_Speed > m_max_speed)
        m_Speed = m_max_speed;
    IBullet::Update();
}