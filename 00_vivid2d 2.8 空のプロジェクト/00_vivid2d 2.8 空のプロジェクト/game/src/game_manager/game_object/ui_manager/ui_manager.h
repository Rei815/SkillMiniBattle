
/*!
 *  @file       ui_manager.h
 *  @brief      UI�Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"
#include "ui/ui.h"
#include <list>
 /*!
  *  @class      CUIManager
  *
  *  @brief      UI�Ǘ��N���X
  *
  *  @author     Kazuya Maruyama
  *
  *  @date       2020/11/13
  *
  *  @since      1.0
  */
class CUIManager
{
public:
    /*!
     *  @brief      �C���X�^���X�̎擾
     *
     *  @return     �C���X�^���X
     */
    static CUIManager& GetInstance(void);

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
     *  @brief      UI����
     *
     *  @param[in]  id          UI��ID
     */
    void        Create(UI_ID id);

    /*!
     *  @brief      UI����
     *
     *  @param[in]  id          UI��ID
     *  @param[in]  position    UI�̈ʒu
     */
    void        Create(UI_ID id, const CVector3& position);

    /*!
     *  @brief      UI����
     *
     *  @param[in]  id          UI��ID
     *  @param[in]  transform    UI�̃g�����X�t�H�[��
     */
    void        Create(UI_ID id, const CTransform& transform);

    /*!
     *  @brief      UI�폜
     *
     *  @param[in]  id          UI��ID
     */
    void        Delete(UI_ID id);

    /*!
     *  @brief      �w��̑�����UI�����邩�m�F
     *
     *  @return     true:UI������
     */
    bool        CheckUIAttribute(CUI::UI_ATTRIBUTE ui_attribute);


    /*!
     *  @brief      ��V���󂯎���������擾
     *
     *  @return     ��V���󂯎�������ǂ���
     * 
     */
    bool GetReceivedReward(void);

    /*!
     *  @brief      ��V���󂯎��������ݒ�
     *
     */
    void SetReceivedReward(bool active);

    /*!
     *  @brief      WaveClearUI�̃A�N�e�B�u���擾
     *
     *  @return     WaveClearUI�̃A�N�e�B�u
     * 
     */
    bool GetWaveClearUIActive(void);

    /*!
     *  @brief      WaveClearUI�̃A�N�e�B�u��ݒ�
     *
     */
    void SetWaveClearUIActive(bool active);

    /*!
     *  @brief      �w���UI�̃A�N�e�B�u���擾
     *
     *  @return     1  �A�N�e�B�u
     *  @return     0 ��A�N�e�B�u
     *  @return     -1 ���݂��Ȃ�
     *
     */
    int GetUIActive(UI_ID ui_id);

private:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CUIManager(void);

    /*!
     *  @brief      �R�s�[�R���X�g���N�^
     *
     *  @param[in]  rhs     �I�u�W�F�N�g
     */
    CUIManager(const CUIManager& rhs);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CUIManager(void);

    /*!
     *  @brief      ������Z�q
     *
     *  @param[in]  rhs ����I�u�W�F�N�g
     *
     *  @return     ���g�̃I�u�W�F�N�g
     */
    CUIManager& operator=(const CUIManager& rhs);

    /*!
     *  @brief      UI���X�g�^
     */
    using UI_LIST = std::list<CUI*>;

    UI_LIST             m_UIList;             //!< UI���X�g

    bool                m_ReceivedReward;
    bool                m_WaveClearUIActiveFlag;
};