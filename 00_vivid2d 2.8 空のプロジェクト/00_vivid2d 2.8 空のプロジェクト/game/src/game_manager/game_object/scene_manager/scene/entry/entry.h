#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include <list>
#include "..\..\..\controller_manager\controller\controller.h"
#include "..\..\..\unit_manager\unit\unit_id.h"
class CEntry : public IScene
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CEntry(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CEntry(void);

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
    std::list<CController*> m_PlayerControllerList;
    static const CVector3   m_spawn_position;
    static const float      m_respawn_height;
    static const CVector3   m_camera_position;
    static const CVector3   m_camera_direction;
    UNIT_ID                 m_UnitID;
    UNIT_ID                 m_PlayerArray[4];
};
