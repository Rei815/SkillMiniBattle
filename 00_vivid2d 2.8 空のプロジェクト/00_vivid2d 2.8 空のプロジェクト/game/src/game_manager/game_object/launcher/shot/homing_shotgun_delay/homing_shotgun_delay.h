#pragma once

#include "..\shot.h"
class CHomingShotgunDelay : public CShot
{
public:
    CHomingShotgunDelay();
    ~CHomingShotgunDelay();

private:

    static const BulletParameters        m_bullet_parameters;

};