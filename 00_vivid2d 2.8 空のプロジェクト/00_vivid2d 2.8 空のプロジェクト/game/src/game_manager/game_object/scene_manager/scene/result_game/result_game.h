#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include "../../../sound_manager/sound_manager.h"

class CResultGame : public IScene
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CResultGame(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CResultGame(void);

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

    STATE           m_State;                //!< ���ID
    BGM_ID          m_Sound;                //
};
