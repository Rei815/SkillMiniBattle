#pragma once

#include "..\game.h"
#include "..\..\..\..\ui_manager\ui\ui_id.h"
class CFallGame : public CGame
{
public:

    /*!
     *  @brief      �R���X�g���N�^
     */
    CFallGame(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CFallGame(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(void);

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

private:

    struct FALL_INFO
    {
        IObject*    object;
        UI_ID       uiID = UI_ID::NONE;
    };

    /*!
     *  @brief      �X�^�[�g
     */
    void    Start(void);

    /*!
     *  @brief      �v���C
     */
    void    Play(void);

    /*!
     *  @brief      �I��
     */
    void    Finish(void);

    /*!
     *  @brief      �I������
     */
    void    CheckFinish(void) override;

    /*!
     *  @brief      ������I�u�W�F�N�g�̑I��
     * 
     *  @return     �I�u�W�F�N�gID
     */
    FALL_INFO    ChooseObject(void);

    static const CTransform         m_object_transform_list[];
    static const float              m_time_accelerator;
    static const float              m_min_time;
    static const float              m_initial_time;
    static const float              m_object_delay_time;
    static const float              m_defeat_height;
    static const CVector3           m_camera_position;
    static const CVector3           m_camera_direction;
    float                           m_FallTime;
    CTimer                          m_ChooseObjectTimer;

    IObject* m_Object;
};
