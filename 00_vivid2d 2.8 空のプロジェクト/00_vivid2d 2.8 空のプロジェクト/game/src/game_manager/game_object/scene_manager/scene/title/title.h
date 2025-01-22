#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include "../../../stage/stage.h"

class CTitle
    : public IScene
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CTitle(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CTitle(void);

    /*!
     *  @brief      ������
     */
    void Initialize(SCENE_ID scene_id);

    /*!
     *  @brief      �X�V
     */
    void Update(void);

    /*!
     *  @brief      �`��
     */
    void Draw(void);

    /*!
     *  @brief      ���
     */
    void Finalize(void);

private:
    /*!
     *  @brief  ���ID
     */
    enum class STATE
    {
        WAIT,
    };

    STATE               m_State;                //!< ���ID
    unsigned int        m_Color;
    static const int    m_fade_speed;
    int                 m_FadeSpeed;
};
