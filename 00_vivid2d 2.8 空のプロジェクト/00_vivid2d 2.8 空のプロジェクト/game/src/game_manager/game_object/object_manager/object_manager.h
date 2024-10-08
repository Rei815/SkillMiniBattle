#pragma once

#include "vivid.h"
#include <list>
#include "object/object.h"
#include "object/object_id.h"
#include "../gimmick_manager/gimmick/gimmick_id.h"
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
    IObject*        Create(OBJECT_ID id, const CVector3& pos);

    /*!
     *  @brief      �M�~�b�N�t�^
     *
     *  @param[in]  gimmick_id          �M�~�b�N��ID
     *  @param[in]  object_id           �I�u�W�F�N�g��ID
     */
    void        SetGimmick(GIMMICK_ID gimmick_id, OBJECT_ID object_id);

    /*!
     *  @brief      �I�u�W�F�N�g���X�g�^
     */
    using OBJECT_LIST = std::list<IObject*>;

    OBJECT_LIST GetList();
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

    static const std::string    m_file_name_list[];

};