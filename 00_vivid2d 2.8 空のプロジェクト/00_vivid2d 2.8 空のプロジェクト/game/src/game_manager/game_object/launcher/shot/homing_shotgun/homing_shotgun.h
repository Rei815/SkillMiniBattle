#pragma once

#include "..\shot.h"
class CHomingShotgun : public CShot
{
public:
    CHomingShotgun();
    ~CHomingShotgun();

private:

    static const BulletParameters        m_bullet_parameters;

};