#pragma once

#include "..\shot.h"
class CShotgun : public CShot
{
public:
    CShotgun();
    ~CShotgun();


private:

    static const BulletParameters        m_bullet_parameters;

};