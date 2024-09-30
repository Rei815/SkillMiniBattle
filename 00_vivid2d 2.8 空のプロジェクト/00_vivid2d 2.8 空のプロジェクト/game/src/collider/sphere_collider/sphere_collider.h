#pragma once

#include "..\collider.h"
class CSphereCollider : public ICollider
{
public:
	CSphereCollider();
	~CSphereCollider();

    /*!
     *  @brief      ‰Šú‰»
     */
    void        Initialize(void);

    /*!
     *  @brief      XV
     */
    void        Update(void);

    /*!
     *  @brief      ‰ğ•ú
     */
    void        Finalize(void);
private:

    static const float       m_radius;
};