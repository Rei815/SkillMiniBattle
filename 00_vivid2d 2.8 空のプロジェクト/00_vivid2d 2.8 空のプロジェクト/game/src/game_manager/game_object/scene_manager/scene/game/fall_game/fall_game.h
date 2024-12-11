#pragma once

#include "..\game.h"
#include "..\..\..\..\ui_manager\ui\ui_id.h"
#include "../../../../ui_manager/ui/fallout_topic/fallout_topic.h"
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
    void        Initialize(SCENE_ID scene_id);

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

    using TOPIC_LIST = std::list<CFallOutTopic*>;

private:

    struct FALL_INFO
    {
        IObject*    object;
        MARK_ID     markID = MARK_ID::CIRCLE;
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

    static const CTransform         m_object_transform_list[];  //!< ������I�u�W�F�N�g�̃g�����X�t�H�[��
    static const float              m_time_accelerator;         //!< ������܂ł̑��x�𑝂₷
    static const float              m_min_time;                 //!< ������܂ł̍ŏ�����
    static const float              m_initial_time;             //!< ������܂ł̏�������
    static const float              m_object_delay_time;        //!< �Ē��I�܂ł̎���
    static const float              m_add_topic_time;           //!< ���肪������܂ł̎���
    static const float              m_defeat_height;            //!< �����鍂��
    static const CVector3           m_camera_position;          //!< �J�����̈ʒu
    static const CVector3           m_camera_direction;         //!< �J�����̕���
    static const vivid::Vector2     m_topic_positionList[];     //!< ����ʒu

    float                           m_FallTime;                 //!< ������܂ł̎���
    CTimer                          m_ChooseObjectTimer[6];        //!< ���I�^�C�}�[
    CTimer                          m_AddTopicTimer;            //!< ���肪������^�C�}�[
    IObject*                        m_Object;                   //!< �I�u�W�F�N�g
    TOPIC_LIST                      m_TopicList;                //!< ����̃��X�g
};
