
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
    CUI*        Create(UI_ID id);

    /*!
     *  @brief      UI����
     *
     *  @param[in]  id          UI��ID
     *  @param[in]  layerNum    UI�̕`�揇
     */
    CUI*        Create(UI_ID id, int layerNum);

    /*!
     *  @brief      UI����
     *
     *  @param[in]  id          UI��ID
     *  @param[in]  position    UI�̈ʒu
     */
    CUI*        Create(UI_ID id, const vivid::Vector2& position);

    /*!
     *  @brief      UI����
     *
     *  @param[in]  id          UI��ID
     *  @param[in]  position    UI�̈ʒu
     *  @param[in]  layerNum    UI�̕`�揇
     */
    CUI*        Create(UI_ID id, const vivid::Vector2& position, int layerNum);

    /*!
     *  @brief      UI����
     *
     *  @param[in]  id          UI��ID
     *  @param[in]  position    UI�̈ʒu
     *  @param[in]  parent      �e��UI
     */
    CUI*        Create(UI_ID id, const vivid::Vector2& position, CUI* parent);

    /*!
     *  @brief      UI����
     *
     *  @param[in]  id          UI��ID
     *  @param[in]  position    UI�̈ʒu
     */
    CUI*        Create(UI_ID id, const CVector3& position);

    /*!
     *  @brief      UI����
     *
     *  @param[in]  id          UI��ID
     *  @param[in]  transform    UI�̃g�����X�t�H�[��
     */
    CUI*        Create(UI_ID id, const CTransform& transform);

    /*!
     *  @brief      UI����
     *
     *  @param[in]  id          UI��ID
     *  @param[in]  transform    UI�̃g�����X�t�H�[��
     *  @param[in]  layerNum    UI�̕`�揇

     */
    CUI*        Create(UI_ID id, const CTransform& transform, int layerNum);

    /*!
     *  @brief      UI�폜
     *
     *  @param[in]  id          UI��ID
     */
    void        Delete(UI_ID id);

    /*!
     *  @brief      UI�폜
     *
     *  @param[in]  ui          UI�̃|�C���^
     */
    void        Delete(const CUI* ui_pointer);

    /*!
     *  @brief      �w���UI�̃A�N�e�B�u���擾
     *
     *  @return     1  �A�N�e�B�u
     *  @return     0 ��A�N�e�B�u
     *  @return     -1 ���݂��Ȃ�
     *
     */
    int GetUIActive(UI_ID ui_id);

    /*!
     *  @brief      UI���X�g�^
     */
    using UI_LIST = std::list<CUI*>;

    /*!
     *  @brief      ���X�g�擾
     *
     *  @return     �I�u�W�F�N�g���X�g
     */
    UI_LIST GetList();

    /*!
     *  @brief      ���C���[���̔ԍ������Ƃɕ��ёւ�
     */
    void            SortList(void);

private:
    /*!
     *  @brief      UI�̃N���X���쐬
     *
     *  @param[in]  id     UI��ID
     */
    CUI*            CreateClass(UI_ID id);


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

    UI_LIST             m_UIList;             //!< UI���X�g
};