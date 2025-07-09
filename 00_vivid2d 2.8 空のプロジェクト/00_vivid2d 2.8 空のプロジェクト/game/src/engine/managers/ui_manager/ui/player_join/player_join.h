#include "..\ui.h"
#include "../../../../../game/components/player_component/player_id.h"
class CPlayerJoin : public CUI
{
public:
    CPlayerJoin(UI_ID id);
    ~CPlayerJoin();

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
     *  @brief      �v���C���[�Q���󋵂̃Z�b�g
     */
    void        SetPlayer(PLAYER_ID id, bool join);

private:
    static const std::string        m_file_names[];
    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const vivid::Vector2     m_offset;           //!< �摜���m�̕�
    static const vivid::Vector2     m_position;         //!< �ʒu
    static const unsigned int       m_color_dark;       //!< �F
    static const unsigned int       m_color_light;      //!< �F

    static const vivid::Rect        m_rect;             //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;           //!< ��_
    static const vivid::Vector2     m_scale;            //!< �g�k
    unsigned int                    m_Color[4];          //!< �F
    bool                            m_ReadyFlag;        //!< ���������̃t���O
};