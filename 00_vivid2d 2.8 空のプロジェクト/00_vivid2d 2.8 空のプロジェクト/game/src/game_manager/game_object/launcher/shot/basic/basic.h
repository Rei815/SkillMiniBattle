#pragma once

#include "..\shot.h"
class CBasic : public CShot
{
public:
    CBasic();
    ~CBasic();

private:
    static const BulletParameters        m_bullet_parameters;

};