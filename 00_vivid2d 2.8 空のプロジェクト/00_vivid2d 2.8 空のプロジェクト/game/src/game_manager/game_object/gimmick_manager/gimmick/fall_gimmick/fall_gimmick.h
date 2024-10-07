
#pragma once
#include "..\gimmick.h"
#include "fall_object/fall_object.h"
#include <list>
class CFallGimmick : public CGimmick
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     */
    CFallGimmick();

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CFallGimmick(void);

    /*!
     *  @brief      ������
     *
     */
    void    Initialize();

    /*!
     *  @brief      �X�V
     */
    void    Update(void);

    /*!
     *  @brief      �`��
     */
    void    Draw(void);

    /*!
     *  @brief      ���
     */
    void    Finalize(void);

    /*!
     *  @brief      �I�u�W�F�N�g����
     *
     *  @param[in]  id              �I�u�W�F�N�g��ID
     */
    void        Create(MARK_ID id, const CVector3& position);

    void        Fall(MARK_ID id);
private:
    /*!
     *  @brief      �t�H�[���I�u�W�F�N�g���X�g�^
     */
    using FALL_OBJECT_LIST = std::list<CFallObject*>;

    FALL_OBJECT_LIST             m_FallObjectList;             //!< �t�H�[���I�u�W�F�N�g���X�g

};
