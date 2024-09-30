#pragma once

#include "..\shot.h"
class CBurst : public CShot
{
public:
    CBurst();
    ~CBurst();

private:
    static const BulletParameters        m_bullet_parameters;

};