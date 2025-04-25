#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "..\..\..\scene_manager\scene\game\game_id.h"
#include "..\..\..\..\..\primitive\primitive.h"
#include "../../../animation_manager/animation/animation.h"

class CPlaneGameImage : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CPlaneGameImage(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CPlaneGameImage(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(const CTransform& transform);

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

    /*!
     *  @brief      �ݒ肳��Ă���Q�[����ID���擾
     * 
     *  @return     �Q�[����ID
     */
    GAME_ID         GetGameID(void);

    /*!
     *  @brief      �Q�[����ID��ݒ�
     * 
     *  @param[in]  game_id     �Q�[����ID
     */
    void            SetGameID(GAME_ID game_id);

    /*!
     *  @brief      �g�����X�t�H�[���ݒ�
     *
     *  @param[in]  transform  �g�����X�t�H�[��
     */
    void            SetTransform(const CTransform& transform);

    /*!
     *  @brief      ���S�ʒu����̊p�x�ݒ�
     *
     *  @param[in]  angle  ���S�ʒu����̊p�x
     */
    void            SetPosAngle(float angle);

    /*!
     *  @brief      �ړ����x�ݒ�
     *
     *  @param[in]  speed  �ړ����x
     */
    void            SetSpeed(float speed);

    /*!
     *  @brief      �A�j���[�V�����擾
     *
     *  @return     �A�j���[�V����
     */
    IAnimation*     GetAnimation(void);

    /*!
     *  @brief      �A�j���[�V�����ݒ�
     *
     *  @param[in]  animation  �A�j���[�V����
     */
    void            SetAnimation(IAnimation* animation);

private:


    static const std::string        m_file_names[];
    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const vivid::Rect        m_rect;             //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;           //!< ��_
    static const CVector3           m_scale;            //!< �g�k
    static const float              m_rotation_speed;
    static const float              m_speed;            //!< �ʒu�����ɉ�]���鑬��

    float                           m_Speed;
    std::string                     m_FileName;
    int                             m_Width;
    int                             m_Height;
    int                             m_Handle;
    float                           m_Angle;            //!< ���g�̉�]
    float                           m_PosAngle;         //!< �ʒu�����ɉ�]
    CPlane                          m_Plane;            //!< ����
    CVector3                        m_InitialPosition;  //!< �����ʒu
    GAME_ID                         m_GameID;           //!< �摜�̃Q�[��ID
    CMatrix                         m_Matrix;
    IAnimation*                     m_Animation;
};
