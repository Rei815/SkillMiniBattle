#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include "../../../stage/stage.h"

class CSelectMode
    : public IScene
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CSelectMode(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSelectMode(void);

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
};
