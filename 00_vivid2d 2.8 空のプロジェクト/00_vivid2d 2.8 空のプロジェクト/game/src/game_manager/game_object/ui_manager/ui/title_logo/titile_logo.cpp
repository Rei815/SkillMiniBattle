#include "title_logo.h"
#include "../../../unit_manager/unit_manager.h"

const vivid::Vector2    CTitleLogo::m_position = vivid::Vector2(0, 0);
const int    CTitleLogo::m_width = 1280;
const int    CTitleLogo::m_height = 780;

/*
 *  �R���X�g���N�^
 */
CTitleLogo::CTitleLogo(UI_ID id)
    : CUI(m_width, m_height, id, -2)
{
}

/*
 *  �f�X�g���N�^
 */
CTitleLogo::~CTitleLogo(void)
{
}

/*
 *  ������
 */
void
CTitleLogo::Initialize(void)
{
}

/*
 *  �X�V
 */
void
CTitleLogo::Update(void)
{

}

/*
 *  �`��
 */
void
CTitleLogo::Draw(void)
{
    vivid::DrawTexture("data\\Textures\\title_logo.png", m_position, 0xffffffff);


}

/*
 *  ���
 */
void
CTitleLogo::Finalize(void)
{

}
