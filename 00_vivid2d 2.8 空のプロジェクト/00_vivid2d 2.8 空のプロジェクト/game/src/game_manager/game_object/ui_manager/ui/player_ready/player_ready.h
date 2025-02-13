#include "..\ui.h"
class CPlayerReady : public CUI
{
public:
    CPlayerReady(UI_ID id);
    ~CPlayerReady();

    /*!
     *  @brief      ������
     */
    void        Initialize();

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
     *  @brief      ���������t���O�̎擾
     *
     *  @return     true    ��������
     *              false   �����ł��Ă��Ȃ�
     */
    bool            GetReadyFlag();

private:
    static const std::string        m_file_names[];
    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const vivid::Vector2     m_offset;           //!< �摜���m�̕�
    static const vivid::Vector2     m_position;         //!< �ʒu
    static const unsigned int       m_color[];          //!< �F

    static const vivid::Rect        m_rect;             //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;           //!< ��_
    static const vivid::Vector2     m_scale;            //!< �g�k
    unsigned int                    m_Color[4];          //!< �F
    bool                            m_ReadyFlag;        //!< ���������̃t���O

};