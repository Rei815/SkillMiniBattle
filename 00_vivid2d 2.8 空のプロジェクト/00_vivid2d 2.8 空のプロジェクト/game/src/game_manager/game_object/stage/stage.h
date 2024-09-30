#pragma once
#include "../model_manager/model/model.h"
#include "../bullet_manager/bullet/bullet.h"
#include "../../../collider/box_collider/box_collider.h"

class CStage
{
public:
    /*!
     *  @brief      �C���X�^���X�̎擾
     *
     *  @return     �C���X�^���X
     */
    static CStage& GetInstance(void);

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

    /*!
     *  @brief      ���f���擾
     */
    CModel        GetModel() const;

    /*!
     *  @brief      ���f���Ƃ̔���
     */
    void CheckHitUnit();
    

    /*!
    *  @brief      �X�e�[�W�̍����擾
    */
    int        GetHeight() const;

    /*!
     *  @brief      �X�e�[�W�̉����擾
     */
    int        GetWidth() const;

    /*!
     *  @brief      �X�e�[�W�̉��s�擾
     */
    int        GetDebth() const;

private:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CStage(void);

    /*!
     *  @brief      �R�s�[�R���X�g���N�^
     *
     *  @param[in]  rhs     �I�u�W�F�N�g
     */
    CStage(const CStage& rhs);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CStage(void);

    /*!
     *  @brief      ������Z�q
     *
     *  @param[in]  rhs ����I�u�W�F�N�g
     *
     *  @return     ���g�̃I�u�W�F�N�g
     */
    CStage& operator=(const CStage& rhs);
    static const int       m_stage_height;
    static const int       m_stage_width;
    static const int       m_stage_debth;
	CModel          m_Model;
    CTransform      m_Transform;
    CBoxCollider    m_BoxCollider;
};