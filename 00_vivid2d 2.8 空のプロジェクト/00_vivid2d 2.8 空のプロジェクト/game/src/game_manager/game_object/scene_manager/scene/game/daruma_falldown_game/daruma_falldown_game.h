#pragma once

#include "..\game.h"

class CDaruma_FallDownGame : public CGame
{
public:
	CDaruma_FallDownGame();
	~CDaruma_FallDownGame();

    /*!
 *  @brief      ‰Šú‰»
 */
    void        Initialize(void);

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

};