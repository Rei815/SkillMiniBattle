#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../skill_manager/skill/skill_id.h"
#include "../../../../../game/components/player_component/player_id.h"

class CSkillCursor : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CSkillCursor(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSkillCursor(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(vivid::Vector2 position);

    /*!
     *  @brief      �X�V
     */
    void        Update(void);

    /*!
     *  @brief      �`��
     */
    void        Draw(void);

    /*!
     *  @brief      ���
     */
    void        Finalize(void);

    void        SetCursor(PLAYER_ID player_id, vivid::Vector2 position, float scale);
    void        SetCursor(PLAYER_ID player_id, vivid::Vector2 position, vivid::Vector2 scale);

    void        SetPlayer(PLAYER_ID player_id);

    void        SetPosition(const vivid::Vector2& position);

private:
    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const vivid::Rect        m_rect;             //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;           //!< ��_
    static const vivid::Vector2     m_default_scale;            //!< �g�k

    static const std::string        m_cursorFileName[];

    bool                            m_Selected;

    std::string                     m_FileName;
};
