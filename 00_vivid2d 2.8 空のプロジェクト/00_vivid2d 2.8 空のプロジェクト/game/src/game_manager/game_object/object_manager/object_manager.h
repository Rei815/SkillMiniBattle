#pragma once

#include "vivid.h"
#include <list>
#include "object/object.h"
#include "object/object_id.h"
class CObjectManager
{
public:
    /*!
     *  @brief      �C���X�^���X�̎擾
     *
     *  @return     �C���X�^���X
     */
    static CObjectManager& GetInstance(void);

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
     *  @brief      �I�u�W�F�N�g����
     *
     *  @param[in]  id              �I�u�W�F�N�gID
     */
    void        Create(OBJECT_ID id, const CVector3& pos);

private:

    /*!
     *  @brief      �I�u�W�F�N�g�X�V
     */
    void        UpdateObject(void);


    /*!
     *  @brief      �R���X�g���N�^
     */
    CObjectManager(void);

    /*!
     *  @brief      �R�s�[�R���X�g���N�^
     *
     *  @param[in]  rhs     �I�u�W�F�N�g
     */
    CObjectManager(const CObjectManager& rhs);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CObjectManager(void);

    /*!
     *  @brief      ������Z�q
     *
     *  @param[in]  rhs ����I�u�W�F�N�g
     *
     *  @return     ���g�̃I�u�W�F�N�g
     */
    CObjectManager& operator=(const CObjectManager& rhs);

    /*!
     *  @brief      �I�u�W�F�N�g���X�g�^
     */
    using OBJECT_LIST = std::list<IObject*>;

    OBJECT_LIST             m_ObjectList;             //!< �I�u�W�F�N�g���X�g
};