#include "ui.h"
#include "..\..\unit_manager\unit_manager.h"

/*
 *  �R���X�g���N�^
 */
CUI::
CUI(int width, int height, UI_ID id)
    : m_ActiveFlag(true)
    , m_Attributes{ CUI::UI_ATTRIBUTE::NONE }
    , m_Width(width)
    , m_Height(height)
    , m_UI_ID(id)
    , m_Transform()
{
}
/*
 *  �f�X�g���N�^
 */
CUI::
~CUI(void)
{
}

/*
 *  ������
 */
void
CUI::
Initialize(void)
{
}

void CUI::Initialize(const CVector3& position)
{
    m_Transform.position = position;
}

void CUI::Initialize(const vivid::Vector2& position)
{
    m_Position = position;
}

void CUI::Initialize(const CTransform& transform)
{
    m_Transform = transform;
}

/*
 *  �X�V
 */
void
CUI::
Update(void)
{

}

/*
 *  �`��
 */
void
CUI::
Draw(void)
{

}

/*
 *  ���
 */
void
CUI::
Finalize(void)
{
}

/*
 *  �A�N�e�B�u�t���O�擾
 */
bool
CUI::
GetActive(void)
{
    return m_ActiveFlag;
}

/*
 *  �A�N�e�B�u�t���O�ݒ�
 */
void
CUI::
SetActive(bool active)
{
    m_ActiveFlag = active;
}

bool CUI::CheckAttribute(UI_ATTRIBUTE attribute)
{
    for (int i = 0; i < m_Attributes.size(); i++)
    {
        if (m_Attributes[i] == attribute)
            return true;
    }
    return false;
}

bool CUI::OnMouseClick(const vivid::Vector2& position, int width, int height)
{
    if (vivid::mouse::Trigger(vivid::mouse::BUTTON_ID::LEFT))
    {
        vivid::Point mouse_pos = vivid::mouse::GetCursorPos();
        if (position.x - width / 2.0f < mouse_pos.x && mouse_pos.x < position.x + width / 2.0f &&
            position.y < mouse_pos.y && mouse_pos.y < position.y + height)
            return true;
        else return false;
    }
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

