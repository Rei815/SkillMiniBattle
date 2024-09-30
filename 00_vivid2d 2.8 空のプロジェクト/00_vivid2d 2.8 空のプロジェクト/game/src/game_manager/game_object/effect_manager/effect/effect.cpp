#include "effect.h"
#include "..\..\..\..\utility\utility.h"
#include <EffekseerForDXLib.h>

IEffect::IEffect()
    : m_Scale(1.0f)
    , m_ActiveFlag(true)
    , m_PlayHandle(VIVID_DX_ERROR)
    , m_ParentPos(nullptr)
{
}

/*
  *  �R���X�g���N�^
  */
IEffect::
IEffect(const std::string& file_name, EFFECT_ID effectID)
    : m_Scale(25.0f)
    , m_ActiveFlag(true)
    , m_FileName(file_name)
    , m_PlayHandle(VIVID_DX_ERROR)
    , m_ParentPos(nullptr)
    , m_EffectID(effectID)
{
}
/*
 *  �R���X�g���N�^
 */
IEffect::
IEffect(int width, int height)
    : m_Width(width)
    , m_Height(height)
    , m_Position2D(vivid::Vector2(0.0f, 0.0f))
    , m_Color(0xffffffff)
    , m_Anchor(vivid::Vector2((float)m_Width / 2.0f, (float)m_Height / 2.0f))
    , m_Rect({ 0, 0, m_Width, m_Height })
    , m_Scale2D(vivid::Vector2(1.0f, 1.0f))
    , m_Rotation(0.0f)
    , m_ActiveFlag(true)
    , m_ParentPos(nullptr)
    , m_EffectID()
{
}

/*
 *  �f�X�g���N�^
 */
IEffect::
~IEffect(void)
{
}

/*
 *  ������
 */
void
IEffect::
Initialize(const vivid::Vector2& position, unsigned int color, float rotation)
{
    m_Position2D = position;
    m_Color = color;
    m_Rotation = rotation;
    m_ActiveFlag = true;
}

/*
 *  ������
 */
void
IEffect::
Initialize(const CVector3& position)
{
    m_Transform.position = position;
    m_ActiveFlag = true;
    m_Scale = 25.0f;
    Load(m_FileName);

}

void IEffect::Initialize(const CVector3& position, const float scale)
{
    m_Transform.position = position;
    m_ActiveFlag = true;
    m_Scale = scale;
    Load(m_FileName);

}

void IEffect::Load(const std::string& file_name)
{
    // �G�t�F�N�g���\�[�X��ǂݍ��ށB
    // �ǂݍ��ގ��ɑ傫�����w�肷��B
    vivid::effekseer::LoadEffect(file_name);

    Start();

}

void IEffect::Start()
{
        m_PlayHandle = vivid::effekseer::StartEffect(m_FileName, m_Transform.position, m_Scale);
}

/*
 *  �X�V
 */
void
IEffect::
Update(void)
{
    if (!vivid::effekseer::IsEffectPlaying(m_PlayHandle))
        m_ActiveFlag = false;
}

/*
 *  �`��
 */
void
IEffect::
Draw(void)
{
    vivid::effekseer::DrawEffect(m_PlayHandle, m_Transform.position);
}

/*
 *  ���
 */
void
IEffect::
Finalize(void)
{
    if (m_PlayHandle != VIVID_UNUSED_HANDLE)
        vivid::effekseer::StopEffect(m_PlayHandle);
}

/*
 *  �ʒu�擾
 */
CVector3
IEffect::
GetPosition(void)
{
    return m_Transform.position;
}

/*
 *  �ʒu�ݒ�
 */
void
IEffect::
SetPosition(const CVector3& position)
{
    if(m_PlayHandle != VIVID_DX_ERROR)
    m_Transform.position = position;
}

/*
 *  �A�N�e�B�u�t���O�擾
 */
bool
IEffect::
GetActive(void)
{
    return m_ActiveFlag;
}

/*
 *  �A�N�e�B�u�t���O�擾
 */
void
IEffect::
SetActive(bool active)
{
    m_ActiveFlag = active;
}

void IEffect::SetParentPosition(CVector3& parentPos)
{
    m_ParentPos = &parentPos;
}

EFFECT_ID IEffect::GetEffectID(void)
{
    return m_EffectID;
}

int IEffect::GetEffectHandle(void)
{
    return m_PlayHandle;
}
