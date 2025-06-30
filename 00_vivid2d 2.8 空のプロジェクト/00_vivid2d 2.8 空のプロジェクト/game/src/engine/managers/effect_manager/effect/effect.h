#pragma once

#include "vivid.h"
#include "effect_id.h"
#include "../../../../mathematics/mathematics.h"
#include "../../../../utility/utility.h"
#include "../../unit_manager/unit/unit.h"

class IEffect
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    IEffect();

    /*!
     *  @brief      �R���X�g���N�^
     */
    IEffect(const std::string& file_name, EFFECT_ID effectID, float speed = 1.0f);

    /*!
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  width   ��
     *  @param[in]  height  ����
     */
    IEffect(int width, int height);

    /*!
     *  @brief      �f�X�g���N�^
     */
    virtual ~IEffect(void);

    /*!
     *  @brief      ������
     *
     *  @param[in]  position    �ʒu
     *  @param[in]  color       �F
     *  @param[in]  rotation    ��]�l
     */
    virtual void    Initialize(const vivid::Vector2& position, unsigned int color, float rotation);

    /*!
     *  @brief      ������
     *
     *  @param[in]  position    �ʒu
     *  @param[in]  scale       �g�嗦
     */

    virtual void    Initialize(const CVector3& position = CVector3::ZERO, float scale = 1.0f);

    /*!
     *  @brief      ������
     *
     *  @param[in]  position    �ʒu
     *  @param[in]  rotation    ��]
     *  @param[in]  scale       �g�嗦
     */

    virtual void    Initialize(const CVector3& position, const CVector3& rotation, const CVector3& scale);

    /*!
     *  @brief      ������
     *
     *  @param[in]  position    �ʒu
     *  @param[in]  rotation    ��]
     *  @param[in]  scale       �g�嗦
     *  @param[in]  speed       �Đ����x
     */

    virtual void    Initialize(const CVector3& position, const CVector3& rotation = CVector3::ZERO, float scale = 1.0f, float speed = 1.0f);

    /*!
     *  @brief      �G�t�F�N�g�̓ǂݍ���
     *
     *  @param[in]  file_name    �t�@�C����
     */
    void	        Load(const std::string& file_name);

    /*!
     *  @brief      �Đ�
     */
    void            Start();

    /*!
     *  @brief      �ꎞ��~
     */
    void            Pause();

    /*!
     *  @brief      �ĊJ
     */
    void            Resume();


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
     *  @brief      �ʒu�擾
     *
     *  @return     �ʒu
     */
    CVector3        GetPosition(void);

    /*!
     *  @brief      �ʒu�ݒ�
     *
     *  @param[in]  position    �ʒu
     */
    void            SetPosition(const CVector3& position);

    /*!
     *  @brief      ��]�擾
     *
     *  @return     ��]
     */
    CVector3        GetRotation(void);

    /*!
     *  @brief      ��]�ݒ�
     *
     *  @param[in]  position    ��]
     */
    void           SetRotation(const CVector3& rotation);

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
     *  @brief      �e
     *
     *  @param[in]  parent  �e
     */
    void            SetParent(std::shared_ptr<IUnit> unit);

    /*!
     *  @brief      �G�t�F�N�gID�擾
     *
     *  @return     �G�t�F�N�gID
     */
    EFFECT_ID       GetEffectID(void);

    /*!
     *  @brief      �G�t�F�N�g�n���h���擾
     *
     *  @return     �G�t�F�N�g�n���h��
     */
    int             GetEffectHandle(void);

protected:
    int			            m_PlayHandle;   //!< �n���h��
    CTransform              m_Transform;    //!< �g�����X�t�H�[��
    std::string             m_FileName;     //!< �G�t�F�N�g�̃t�@�C����
    CVector3                m_Scale;        //!< �g�嗦
    bool                    m_ActiveFlag;   //!< �A�N�e�B�u�t���O
    int                     m_Width;        //!< ��
    int                     m_Height;       //!< ����
    vivid::Vector2          m_Position2D;   //!< �ʒu
    unsigned int            m_Color;        //!< �F
    vivid::Vector2          m_Anchor;       //!< ��_
    vivid::Rect             m_Rect;         //!< �ǂݍ��ݔ͈�
    vivid::Vector2          m_Scale2D;      //!< 2D�̊g�嗦
    float                   m_Rotation;     //!< ��]�l
    std::shared_ptr<IUnit>  m_Parent;       //!< �e
    EFFECT_ID               m_EffectID;     //!< �G�t�F�N�gID
    float                   m_Speed;        //!< �Đ����x
    bool                    m_StopFlag;     //!< �Đ���~�t���O
};
