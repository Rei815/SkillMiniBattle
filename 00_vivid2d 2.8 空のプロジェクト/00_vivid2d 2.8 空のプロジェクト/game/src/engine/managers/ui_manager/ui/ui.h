#pragma once

#include "vivid.h"
#include<vector>
#include "ui_id.h"
#include "../../../../utility/utility.h"
#include "../../scene_manager/scene/scene_id.h"
#include <memory>
class CUI : public std::enable_shared_from_this<CUI>
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CUI(UI_ID id, int layer = 0);
    /*!
     *  @brief      �R���X�g���N�^
     */
    CUI(int width, int height, UI_ID id, int layer = 0);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CUI(void);

    /*!
     *  @brief      ������
     */
    virtual void    Initialize(void);

    /*!
     *  @brief      ������
     * 
     *  @param[in]  position    �ʒu(3D)
     */
    virtual void    Initialize(const CVector3& position);

    /*!
     *  @brief      ������
     *
     *  @param[in]  position    �ʒu(2D)
     */
    virtual void    Initialize(const vivid::Vector2& position);

    /*!
     *  @brief      ������
     *
     *  @param[in]  transform   �g�����X�t�H�[��
     */
    virtual void    Initialize(const CTransform& transform);

    /*!
     *  @brief      �X�V
     */
    virtual void    Update(void);

    /*!
     *  @brief      �`��
     */
    virtual void    Draw(void);

    /*!
     *  @brief      ���
     */
    virtual void    Finalize(void);

    /*!
     *  @brief      �A�N�e�B�u�t���O�擾
     *
     *  @return     �A�N�e�B�u�t���O
     */
    bool            IsActive(void);

    /*!
     *  @brief      �폜
     */
    void            Delete();

    /*!
     *  @brief      �ʒu�擾
     *
     *  @return     �ʒu
     */
    vivid::Vector2  GetPosition(void);
    /*!
     *  @brief      �����擾
     *
     *  @return     ����
     */
    int             GetWidth(void);
    /*!
     *  @brief      �����擾
     *
     *  @return     ����
     */
    int             GetHeight(void);
    /*!
     *  @brief      ID�擾
     *
     *  @return     UI��ID
     */
    UI_ID           GetUI_ID(void);

    /*!
     *  @brief      �g�嗦�擾
     *
     *  @return     �g�嗦
     */
    vivid::Vector2  GetScale(void);

    /*!
     *  @brief      ID�ݒ�
     *
     *  @param[in]  id  UI��ID
     */
    void            SetUI_ID(UI_ID id);

    /*!
     *  @brief      �ʒu�ݒ�
     *
     *  @param[in]  position  �ʒu
     */
    void            SetPosition(const vivid::Vector2& position);

    /*!
     *  @brief      �g�嗦�ݒ�
     *
     *  @param[in]  scale  �g�嗦
     */
    void            SetScale(float scale);

    /*!
     *  @brief      �g�嗦�ݒ�
     *
     *  @param[in]  scale  �g�嗦
     */
    void            SetScale(const vivid::Vector2& scale);

    /*!
     *  @brief      �g�����X�t�H�[���擾
     *
     *  @return     �g�����X�t�H�[��
     */
    CTransform      GetTransform(void);

    /*!
     *  @brief      �g�����X�t�H�[���ݒ�
     *
     *  @param[in]  transform  �g�����X�t�H�[��
     */
    void            SetTransform(const CTransform& transform);

    /*!
     *  @brief      �e�̃I�u�W�F�N�g�擾
     *
     *  @return     �e�̃I�u�W�F�N�g
     */
    std::shared_ptr<CUI>        GetParent(void);

    /*!
     *  @brief      �e�̃g�����X�t�H�[���ݒ�
     *
     *  @param[in]  parent  �e�̃g�����X�t�H�[��
     */
    void            SetParent(std::shared_ptr<CUI> parent);

    /*!
     *  @brief      ���C���[���ԍ��擾
     *
     *  @return     ���C���[
     */
    int             GetOrderInLayer(void);

    /*!
     *  @brief      ���C���[���ԍ��ݒ�
     *
     *  @param[in]  num  ���C���[���ԍ�
     */
    void            SetOrderInLayer(int num);

    /*!
     *  @brief      ���C���[���ԍ��̔�r
     */
    bool operator<(const CUI& r) const;

    /*!
     *  @brief      �ݒ肳��Ă���V�[����ID���擾
     *
     *  @return     �V�[��ID
     */
    SCENE_ID        GetSceneID(void);

protected:

    /*!
     *  @brief      �ړ��x�N�g���̎擾
     * 
     *  @return     Vector3     �x�N�g��
     */
    CVector3        GetVelocity();

    CTransform                      m_Transform;        //!< �g�����X�t�H�[��
    vivid::Vector2                  m_Position;         //!< �ʒu
    int                             m_Height;           //!< ����
    int                             m_Width;            //!< ��
    bool                            m_ActiveFlag;       //!< �A�N�e�B�u�t���O
    UI_ID                           m_UI_ID;            //!< ID
    vivid::Vector2                  m_Scale;            //!< �g�嗦
    std::shared_ptr<CUI>            m_Parent;           //!< �e�̃|�C���^
    int                             m_OrderInLayer;     //!< �`�揇
    CVector3                        m_Velocity;         //!< �ړ��x�N�g��
    SCENE_ID                        m_SceneID;          //!< �V�[��ID
};
