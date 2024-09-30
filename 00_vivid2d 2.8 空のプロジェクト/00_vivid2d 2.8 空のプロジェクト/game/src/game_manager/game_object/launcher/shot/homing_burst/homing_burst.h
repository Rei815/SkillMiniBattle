#pragma once

#include "..\shot.h"
class CHomingBurst : public CShot
{
public:
    CHomingBurst();
    ~CHomingBurst();

private:
    static const BulletParameters        m_bullet_parameters;

};