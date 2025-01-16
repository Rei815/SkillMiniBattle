#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include "../../../stage/stage.h"

class CResultMiniGame
    : public IScene
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CResultMiniGame(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CResultMiniGame(void);

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
    static const vivid::Vector2 m_OriginKeyPos;
    static const float          m_KeyOffset;

};
