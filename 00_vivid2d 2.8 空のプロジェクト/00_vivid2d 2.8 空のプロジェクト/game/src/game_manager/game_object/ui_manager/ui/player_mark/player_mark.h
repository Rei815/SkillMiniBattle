#include "..\ui.h"
class CPlayerMark : public CUI
{
public:
    CPlayerMark(UI_ID id);
    ~CPlayerMark();

    /*!
     *  @brief      ������
     */
    void        Initialize(const vivid::Vector2& position);

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

private:
    static const std::string        m_file_names[];
    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const vivid::Rect        m_rect;             //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;           //!< ��_
    static const vivid::Vector2     m_scale;            //!< �g�k

};