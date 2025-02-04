#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../skill_manager/skill/skill_id.h"

class CSkillGauge : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CSkillGauge(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSkillGauge(void);

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

    void        SetGauge(vivid::Vector2 position, float scale);

    void        SetPosition(const vivid::Vector2& position);

    void        SetScale(float scale);

    void        SetPercent(float percent);

private:
    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const vivid::Rect        m_rect;             //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;           //!< ��_
    static const float              m_default_scale;            //!< �g�k
    static const unsigned int       m_background_color;

    static const std::string        m_file_name;
    static const double             m_start_percent;
    
    double              m_Scale;
    vivid::Vector2      m_CenterPosition;

    int m_ImageHandle;
    double m_Percent;
};
