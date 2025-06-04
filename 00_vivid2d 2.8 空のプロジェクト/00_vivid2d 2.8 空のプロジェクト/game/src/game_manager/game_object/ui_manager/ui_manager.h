#pragma once

#include "vivid.h"
#include "ui/ui.h"
#include <list>
#include <memory>
 /*!
  *  @brief      UI�}�l�[�W���[�N���X
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
     *  @param[in]  layerNum    UI�̕`�揇
     */
    std::shared_ptr<CUI>        Create(UI_ID id);

    /*!
     *  @brief      UI����
     *
     *  @param[in]  id          UI��ID
     *  @param[in]  position    UI�̈ʒu
     */
    std::shared_ptr<CUI>        Create(UI_ID id, const vivid::Vector2& position);

    /*!
     *  @brief      UI����
     *
     *  @param[in]  id          UI��ID
     *  @param[in]  position    UI�̈ʒu
     */
    std::shared_ptr<CUI>        Create(UI_ID id, const CVector3& position);

    /*!
     *  @brief      UI����
     *
     *  @param[in]  id          UI��ID
     *  @param[in]  transform    UI�̃g�����X�t�H�[��
     */
    std::shared_ptr<CUI>        Create(UI_ID id, const CTransform& transform);

    /*!
     *  @brief      UI�폜
     *
     *  @param[in]  id          UI��ID
     */
    void            Delete(UI_ID id);

    /*!
     *  @brief      UI���X�g�^
     */
    using UI_LIST = std::list<std::shared_ptr<CUI>>;

    /*!
     *  @brief      ���X�g�擾
     *
     *  @return     �I�u�W�F�N�g���X�g
     */
    UI_LIST         GetList();

    /*!
     *  @brief      ���C���[���̔ԍ������Ƃɕ��ёւ�
     */
    void            SortList(void);

    /*
    *  @brief       UI�擾
    *               ��������ꍇ�ŏ��ɍ��ꂽ���̂��Ԃ��Ă���
     * @param[in]   ui_id          UI��ID
    *  @return      �I�u�W�F�N�g���X�g
    */
    std::shared_ptr<CUI>            GetUI(UI_ID ui_id);

private:
    UI_LIST             m_UIList;             //!< UI���X�g

    /*!
     *  @brief              UI�̃N���X���쐬
     *
     *  @param[in]  id      UI��ID
     */
    std::shared_ptr<CUI>    CreateClass(UI_ID id);


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

};