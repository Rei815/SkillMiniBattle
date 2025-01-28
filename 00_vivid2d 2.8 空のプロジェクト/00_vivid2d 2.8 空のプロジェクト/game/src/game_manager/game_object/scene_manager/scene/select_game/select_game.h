#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include "..\..\..\animation_manager\animation\animation.h"

class CSelectGame
    : public IScene
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CSelectGame(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSelectGame(void);

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
    static const int    m_games_num;
    static const float  m_circle_radius;
    IAnimation*         m_PlaneUp;
};
