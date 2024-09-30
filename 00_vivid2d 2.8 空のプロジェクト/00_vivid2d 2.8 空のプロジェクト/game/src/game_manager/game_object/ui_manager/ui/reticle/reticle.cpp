#include "reticle.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../camera/camera.h"

const int               CReticle::m_height = 32;
const int               CReticle::m_width = 32;
const vivid::Vector2    CReticle::m_position = vivid::Vector2(m_height / 2.0f, m_width / 2.0f);
const vivid::Rect       CReticle::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CReticle::m_scale = vivid::Vector2(1.0f, 1.0f);
const vivid::Vector2    CReticle::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);

/*
 *  コンストラクタ
 */
CReticle::
CReticle(void)
    : CUI(m_width, m_height)
    , m_Scale()
    , m_Color()
{
}

/*
 *  デストラクタ
 */
CReticle::
~CReticle(void)
{
}

/*
 *  初期化
 */
void
CReticle::
Initialize(void)
{
    m_Scale = m_scale;
    m_Color = 0xffffffff;
    // 画像の読み込み
    m_Handle = LoadGraph("data\\Textures\\reticle.png");
    m_HandleRed = LoadGraph("data\\Textures\\reticle_red.png");
}

/*
 *  更新
 */
void
CReticle::
Update(void)
{

}

/*
 *  描画
 */
void
CReticle::
Draw(void)
{
    vivid::Point mousePoint = vivid::mouse::GetCursorPos();
    CVector3 mousePos;
    mousePos.x = mousePoint.x;
    mousePos.y = mousePoint.y;
    mousePos.z = 1.0f;
    CVector3 endPos = ConvScreenPosToWorldPos(mousePos);
    CVector3 startPos = CCamera::GetInstance().GetPosition();
    CVector3 dir = CUnitManager::GetInstance().CheckHitLine(startPos, endPos);
    if (CUnitManager::GetInstance().CheckHitLineEnemy(startPos, endPos) == true)
    {
        m_Scale = m_scale * 1.5f;
        m_Color = 0xffff0000;
        //    DrawBillboard3D(dir, 0.5f, 0.5f, 100.0, 0.0f, m_HandleRed, TRUE);

    }
    else
    {
        m_Scale = m_scale;
        m_Color = 0xffffffff;
        //else DrawBillboard3D(dir, 0.5f, 0.5f, 100.0, 0.0f, m_Handle, TRUE);
    }
    vivid::DrawTexture("data\\Textures\\reticle.png", vivid::Vector2(mousePoint.x, mousePoint.y) - m_position, m_Color, m_rect, m_anchor, m_Scale);
}

/*
 *  解放
 */
void
CReticle::
Finalize(void)
{
    // 読み込んだ画像のグラフィックハンドルを削除
    DeleteGraph(m_Handle);
}
