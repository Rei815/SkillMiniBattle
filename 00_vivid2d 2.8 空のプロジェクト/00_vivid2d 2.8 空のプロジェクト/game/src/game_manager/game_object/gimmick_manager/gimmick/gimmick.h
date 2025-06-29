
#pragma once
#include "gimmick_id.h"
#include "../../../../mathematics/mathematics.h"
#include "../../model/model.h"
#include "..\..\object_manager\object\object.h"
#include "..\..\..\..\utility\utility.h"
#include <memory>
class IObject;
enum class GIMMICK_STATE
{
    WAIT,
    PLAY,
    FINISH,
};

class CGimmick : public std::enable_shared_from_this<CGimmick>
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CGimmick();

    /*!
     *  @brief      �f�X�g���N�^
     */
    virtual ~CGimmick(void);

    /*!
     *  @brief      ������
     * 
     *  @param[in]  object          �I�u�W�F�N�g�̃|�C���^
     */
    virtual void    Initialize(std::shared_ptr<IObject> object);

    /*!
     *  @brief      ������
     * 
     *  @param[in]  object          �I�u�W�F�N�g�̃|�C���^
     *  @param[in]  time            �^�C�}�[�̐ݒ�
     */
    virtual void    Initialize(std::shared_ptr<IObject> object, float time);

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
     *  @brief      �M�~�b�NID�擾
     *
     *  @return     �M�~�b�NID
     */
    GIMMICK_ID      GetGimmickID(void);

    /*!
     *  @brief      �A�N�e�B�u�t���O�擾
     *
     *  @return     �A�N�e�B�u�t���O
     */
    bool            IsActive(void);

    /*!
     *  @brief      �A�N�e�B�u�t���O�ݒ�
     *
     *  @param[in]  active  �A�N�e�B�u�t���O
     */
    void            Delete();

    /*!
     *  @brief      �쓮�t���O�ݒ�
     *
     *  @param[in]  flag  �쓮�t���O
     */
    virtual void    SetOperationFlag(bool flag);

    /*!
     *  @brief      �^�C�}�[�ݒ�
     *
     *  @param[in]  time  ����
     */
    void            SetTimer(float time);

    /*!
     *  @brief      ��Ԏ擾
     *
     *  @return     ���
     */
    GIMMICK_STATE   GetState(void);

    /*!
     *  @brief      ��Ԑݒ�
     *
     *  @param[in]  state  ���
     */
    void            SetState(GIMMICK_STATE state);
protected:
    bool                        m_ActiveFlag;       //!< �A�N�e�B�u�t���O
    std::shared_ptr<IObject>    m_Object;           //!< ���삳����I�u�W�F�N�g
    CTimer                      m_Timer;            //!< �^�C�}�[
    bool                        m_OperationFlag;    //!< �쓮�t���O
    GIMMICK_STATE               m_State;            //!< ���
};
