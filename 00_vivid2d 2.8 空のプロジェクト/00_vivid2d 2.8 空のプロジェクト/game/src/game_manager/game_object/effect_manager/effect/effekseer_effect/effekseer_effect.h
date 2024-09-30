//#pragma once
//
//#include "vivid.h"
//#include "..\effect.h"
//class CEffekseerEffect : 
//{
//public:
//    /*!
//     *  @brief      �R���X�g���N�^
//     */
//    CEffekseerEffect();
//    /*!
//     *  @brief      �R���X�g���N�^
//     */
//    CEffekseerEffect(const std::string& file_name, EFFECT_ID effectID);
//
//    /*!
//     *  @brief      �R���X�g���N�^
//     *
//     *  @param[in]  width   ��
//     *  @param[in]  height  ����
//     */
//    CEffekseerEffect(int width, int height);
//
//    /*!
//     *  @brief      �f�X�g���N�^
//     */
//    virtual ~CEffekseerEffect(void);
//
//    /*!
//     *  @brief      ������
//     *
//     *  @param[in]  position    �ʒu
//     *  @param[in]  color       �F
//     *  @param[in]  rotation    ��]�l
//     */
//    virtual void    Initialize(const vivid::Vector2& position, unsigned int color, float rotation);
//
//    /*!
//     *  @brief      ������
//     *
//     *  @param[in]  position    �ʒu
//     */
//    virtual void    Initialize(const CVector3& position);
//
//    /*!
//     *  @brief      ������
//     *
//     *  @param[in]  position    �ʒu
//     *  @param[in]  scale       �g�嗦
//     */
//
//    virtual void    Initialize(const CVector3& position, const float scale);
//
//    void	Load(const std::string& file_name);
//
//    void    Start();
//    /*!
//     *  @brief      �X�V
//     */
//    virtual void    Update(void);
//
//    /*!
//     *  @brief      �`��
//     */
//    virtual void    Draw(void);
//
//    /*!
//     *  @brief      ���
//     */
//    virtual void    Finalize(void);
//
//    /*!
//     *  @brief      �ʒu�擾
//     *
//     *  @return     �ʒu
//     */
//    CVector3  GetPosition(void);
//
//    /*!
//     *  @brief      �ʒu�ݒ�
//     *
//     *  @param[in]  position    �ʒu
//     */
//    void            SetPosition(const CVector3& position);
//
//    /*!
//     *  @brief      �A�N�e�B�u�t���O�擾
//     *
//     *  @return     �A�N�e�B�u�t���O
//     */
//    bool            GetActive(void);
//
//    /*!
//     *  @brief      �A�N�e�B�u�t���O�ݒ�
//     *
//     *  @param[in]  active  �A�N�e�B�u�t���O
//     */
//    void            SetActive(bool active);
//
//    /*!
//     *  @brief      �e�̈ʒu�ݒ�
//     *
//     *  @param[in]  parentPos  �e�̈ʒu
//     */
//    void            SetParentPosition(CVector3& parentPos);
//
//    /*!
//     *  @brief      �G�t�F�N�gID�擾
//     *
//     *  @return     �G�t�F�N�gID
//     */
//    EFFECT_ID            GetEffectID(void);
//
//    /*!
//     *  @brief      �G�t�F�N�g�n���h���擾
//     *
//     *  @return     �G�t�F�N�g�n���h��
//     */
//    int            GetEffectHandle(void);
//
//protected:
//    int			            m_Handle;		//!< �n���h��
//    CTransform              m_Transform;
//    std::string             m_FileName;     //!< �G�t�F�N�g�̃t�@�C����
//    float                   m_Scale;        //!< �g�嗦
//    bool                    m_ActiveFlag;   //!< �A�N�e�B�u�t���O
//    int                     m_Width;        //!< ��
//    int                     m_Height;       //!< ����
//    vivid::Vector2          m_Position2D;   //!< �ʒu
//    unsigned int            m_Color;        //!< �F
//    vivid::Vector2          m_Anchor;       //!< ��_
//    vivid::Rect             m_Rect;         //!< �ǂݍ��ݔ͈�
//    vivid::Vector2          m_Scale2D;      //!< 2D�̊g�嗦
//    float                   m_Rotation;     //!< ��]�l
//    CVector3* m_ParentPos;
//    EFFECT_ID               m_EffectID;
//};
