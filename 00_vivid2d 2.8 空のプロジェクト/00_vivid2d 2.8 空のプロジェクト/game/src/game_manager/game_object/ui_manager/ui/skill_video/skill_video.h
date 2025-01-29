#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../skill_manager/skill/skill_id.h"
#include "../../../unit_manager/unit/unit_id.h"

class CSkillVideo : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CSkillVideo(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSkillVideo(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(const vivid::Vector2& position);

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

    void        SetPosition(const vivid::Vector2& position);

    void        SetScale(float scale);
    void        SetScale(const vivid::Vector2& scale);

    void        SetSkillVideo(int skill_num, SKILL_ID skill_id);
    void        ResetSkillVideo();

    void        SetSkillNum(int skill_num);

private:
    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const vivid::Vector2     m_default_scale;    //!< �g�k
    static const vivid::Vector2     m_default_position; //!< ���W

    static const std::string        m_skill_video_file_name[];
    int                             m_Handle[(int)UNIT_ID::NONE];
    SKILL_ID                        m_HandleSkillID[(int)UNIT_ID::NONE];

    vivid::Vector2  m_CenterPos;
    int             m_NowSkillNum;
};
