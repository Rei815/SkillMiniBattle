#pragma once

#include "vivid.h"
#include <list>
#include "object/object.h"
#include "object/object_id.h"
#include "../gimmick_manager/gimmick/gimmick_id.h"
#include "..\unit_manager\unit\player\player.h"
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
     *  @param[in]  position        �ʒu
     */
    IObject*    Create(OBJECT_ID id, const CTransform& transform);

    /*!
     *  @brief      �M�~�b�N�t�^
     *
     *  @param[in]  gimmick_id          �M�~�b�N��ID
     *  @param[in]  object              �I�u�W�F�N�g
     */
    void        StartGimmick(GIMMICK_ID gimmick_id, IObject* object);

    /*!
     *  @brief      �M�~�b�N�t�^
     *
     *  @param[in]  gimmick_id          �M�~�b�N��ID
     *  @param[in]  object              �I�u�W�F�N�g
     *  @param[in]  delayFrame          �x������
     */
    void        StartGimmick(GIMMICK_ID gimmick_id, IObject* object, float time);

    /*!
     *  @brief      �I�u�W�F�N�g���X�g�^
     */
    using OBJECT_LIST = std::list<IObject*>;

    /*!
     *  @brief      ���X�g�擾
     *
     *  @return     �I�u�W�F�N�g���X�g
     */
    OBJECT_LIST GetList();

    /*!
     *  @brief      ���������I�u�W�F�N�g��Ԃ�
     *
     *  @param[in]  player          �v���C���[�N���X
     *  @return     �I�u�W�F�N�g(�|�C���^)
     */
    IObject*    CheckHitObject(CPlayer* player);
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

    OBJECT_LIST             m_ObjectList;             //!< �I�u�W�F�N�g���X�g
};