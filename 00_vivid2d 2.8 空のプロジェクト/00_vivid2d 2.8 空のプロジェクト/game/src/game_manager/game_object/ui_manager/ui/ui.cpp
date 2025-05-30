#include "ui.h"
#include "..\..\scene_manager\scene_manager.h"
#include "../ui_manager.h"

CUI::CUI(UI_ID id)
    : m_ActiveFlag(true)
    , m_UI_ID(id)
    , m_Transform()
    , m_Parent(nullptr)
    , m_OrderInLayer(0)
    , m_SceneID(SCENE_ID::MAX)
{
}

/*
 *  コンストラクタ
 */
CUI::CUI(int width, int height, UI_ID id, int layer)
    : m_Width(width)
    , m_Height(height)
    , m_ActiveFlag(true)
    , m_UI_ID(id)
    , m_Transform()
    , m_Parent(nullptr)
    , m_OrderInLayer(layer)
    , m_SceneID(SCENE_ID::MAX)
{
}
/*
 *  デストラクタ
 */
CUI::
~CUI(void)
{
}

/*
 *  初期化
 */
void
CUI::
Initialize(void)
{
    m_SceneID = CSceneManager::GetInstance().GetLastSceneID();
}

void CUI::Initialize(const CVector3& position)
{
    m_SceneID = CSceneManager::GetInstance().GetLastSceneID();

    m_Transform.position = position;
}

void CUI::Initialize(const vivid::Vector2& position)
{
    m_SceneID = CSceneManager::GetInstance().GetLastSceneID();

    m_Position = position;
}

void CUI::Initialize(const CTransform& transform)
{
    m_SceneID = CSceneManager::GetInstance().GetLastSceneID();

    m_Transform = transform;
}

/*
 *  更新
 */
void
CUI::
Update(void)
{
    if (m_Parent)
    {
        CVector3 velocity = m_Parent->GetVelocity();
        m_Position.x += velocity.x;
        m_Position.y += velocity.y;
        m_Transform.position -= velocity;

    }
}

/*
 *  描画
 */
void
CUI::
Draw(void)
{

}

/*
 *  解放
 */
void
CUI::
Finalize(void)
{
    m_ActiveFlag = false;
}

/*
 *  アクティブフラグ取得
 */
bool
CUI::
IsActive(void)
{
    return m_ActiveFlag;
}

/*
 *  アクティブフラグ設定
 */
void
CUI::
SetActive(bool active)
{

    m_ActiveFlag = active;
}

vivid::Vector2 CUI::GetPosition(void)
{
    return m_Position;
}

int CUI::GetWidth(void)
{
    return m_Width;
}

int CUI::GetHeight(void)
{
    return m_Height;
}

UI_ID CUI::GetUI_ID(void)
{
    return m_UI_ID;
}

vivid::Vector2 CUI::GetScale(void)
{
    return m_Scale;
}

void CUI::SetUI_ID(UI_ID id)
{
    m_UI_ID = id;
}

void CUI::SetPosition(const vivid::Vector2& position)
{
    m_Position = position;
}

void CUI::SetScale(float scale)
{
    SetScale(vivid::Vector2(scale, scale));
}

void CUI::SetScale(const vivid::Vector2& scale)
{
    m_Scale = scale;
}

CTransform CUI::GetTransform(void)
{
    return m_Transform;
}

void CUI::SetTransform(const CTransform& transform)
{
    m_Transform = transform;
}

CUI* CUI::GetParent(void)
{
    return m_Parent;
}

void CUI::SetParent(CUI* parent)
{
    m_Parent = parent;
}

int CUI::GetOrderInLayer(void)
{
    return m_OrderInLayer;
}

void CUI::SetOrderInLayer(int num)
{
    m_OrderInLayer = num;
    CUIManager::GetInstance().SortList();
}

bool CUI::operator<(const CUI& r) const
{
    return m_OrderInLayer < r.m_OrderInLayer;
}

SCENE_ID CUI::GetSceneID(void)
{
    return m_SceneID;
}

CVector3 CUI::GetVelocity()
{
    return m_Velocity;
}

