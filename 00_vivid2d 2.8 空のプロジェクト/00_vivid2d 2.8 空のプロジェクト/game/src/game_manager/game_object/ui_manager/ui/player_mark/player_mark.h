#include "..\ui.h"
class CPlayerMark : public CUI
{
public:
    CPlayerMark(UI_ID id);
    ~CPlayerMark();

    /*!
     *  @brief      ‰Šú‰»
     */
    void        Initialize(const vivid::Vector2& position);

    /*!
     *  @brief      XV
     */
    void        Update(void);

    /*!
     *  @brief      •`‰æ
     */
    void        Draw(void);

    /*!
     *  @brief      ‰ğ•ú
     */
    void        Finalize(void);

private:
    static const std::string        m_file_names[];
    static const int                m_height;           //!< ‚‚³
    static const int                m_width;            //!< •
    static const vivid::Rect        m_rect;             //!< “Ç‚İ‚İ”ÍˆÍ
    static const vivid::Vector2     m_anchor;           //!< Šî€“_
    static const vivid::Vector2     m_scale;            //!< Šgk

};