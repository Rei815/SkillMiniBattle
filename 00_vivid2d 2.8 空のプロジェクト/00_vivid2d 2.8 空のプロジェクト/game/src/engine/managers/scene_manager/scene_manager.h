#pragma once

#include "vivid.h"
#include"scene\scene_id.h"
#include <list>
#include "..\controller_manager\controller\controller.h"
#include"scene\game\game.h"

class IScene;
class CController;

class CSceneManager
{
public:

    /*!
      *  @brief      �C���X�^���X�̎擾
      *
      *  @return     �C���X�^���X
      */
    static CSceneManager& GetInstance(void);

    /*!
     *  @brief      ������
     */
    void            Initialize(void);

    /*!
     *  @brief      �X�V
     */
    void            Update(void);

    /*!
     *  @brief      �`��
     */
    void            Draw(void);

    /*!
     *  @brief      �V�[���G�t�F�N�g�`��
     */
    void            DrawSceneEffect(void);

    /*!
     *  @brief      ���
     */
    void            Finalize(void);

    /*!
     *  @brief      �V�[���؂芷��
     *
     *  @param[in]  id  �V�[��ID
     */
    void            ChangeScene(SCENE_ID id);

    /*!
     *  @brief      �V�[����ǉ�����
     *
     *  @param[in]  id  �V�[��ID
     */
    void            PushScene(SCENE_ID id);

    /*!
     *  @brief      �V�[�����폜����
     *
     *  @param[in]  id  �V�[��ID
     */
    void            RemoveScene(SCENE_ID id);

    using SCENE_LIST = std::list<std::shared_ptr<IScene>>;
    SCENE_LIST                  m_SceneList;            //!< �V�[���N���X

    SCENE_LIST  GetList();

    /*!
     *  @brief      �|�[�Y����
     *
     *  @return     �|�[�Y�t���O
     */
    bool            Pausing(void);
    /*!
     *  @brief      �|�[�Y�t���O�ݒ�
     *
     *  @return     �|�[�Y�t���O
     */
    void            SetPauseFlag(bool active);

    /*!
     *  @brief      �ŐV�̃V�[����ID���擾
     *
     *  @return     �ŐV�̃V�[����ID
     */
    SCENE_ID        GetLastSceneID(void);

    void Pause();
private:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CSceneManager(void);

    /*!
     *  @brief      �R�s�[�R���X�g���N�^
     *
     *  @param[in]  rhs     �I�u�W�F�N�g
     */
    CSceneManager(const CSceneManager& rhs);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSceneManager(void);

    /*!
     *  @brief      ������Z�q
     *
     *  @param[in]  rhs ����I�u�W�F�N�g
     *
     *  @return     ���g�̃I�u�W�F�N�g
     */
    CSceneManager& operator=(const CSceneManager& rhs);

    /*!
     *  @brief      �V�[������
     *
     *  @param[in]  id  �V�[��ID
     */
    std::shared_ptr<IScene>     CreateScene(SCENE_ID id);

    /*!
     *  @brief      �t�F�[�h�C��
     */
    void            FadeIn(void);

    /*!
     *  @brief      �V�[���X�V
     */
    void            SceneUpdate(void);

    /*!
     *  @brief      �t�F�[�h�A�E�g
     */
    void            FadeOut(void);

    /*!
     *  @brief      �V�[���ύX
     */
    void            SceneChange();

    /*!
     *  @brief              �V�[���擾
     */
    std::shared_ptr<IScene> GetScene(SCENE_ID scene_id);


    /*!
     *  @brief      ���ID
     */
    enum class STATE
    {
        FADEIN,         //!< �t�F�[�h�C��
        SCENE_UPDATE,   //!< �V�[���X�V
        FADEOUT,        //!< �t�F�[�h�A�E�g
        SCENE_CHANGE    //!< �V�[���ύX
    };

    static const int            m_fade_speed;           //!< �t�F�[�h���x
    static const float          m_wait_time;            //!< �A���t�@�l���ő�ɂȂ������̑ҋ@����

    SCENE_ID                    m_CurrentSceneID;       //!< ���݂̃V�[��ID
    SCENE_ID                    m_NextSceneID;          //!< ���̃V�[��ID

    STATE                       m_State;                //!< ���
    bool                        m_ChangeScene;          //!< �V�[���ύX�t���O
    int                         m_FadeAlpha;            //!< �t�F�[�h���̃A���t�@�l
    unsigned int                m_FadeColor;            //!< �t�F�[�h���̐F
    int                         m_FadeSpeed;            //!< �t�F�[�h�X�s�[�h
    CTimer                      m_SceneChangeWaitTimer; //!< �t�F�[�h��ɃV�[���؂�ւ�����܂ł̃^�C�}�[            
    bool                        m_PauseFlag;            //!< �|�[�Y�t���O
    std::shared_ptr<CController>m_PauseController;      //!< �|�[�Y���Ă���R���g���[���[

};
