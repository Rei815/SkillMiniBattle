#pragma once

#include "..\shot.h"
class CDodgeBall : public CShot
{
public:
    CDodgeBall();
    ~CDodgeBall();

private:
    static const BulletParameters        m_bullet_parameters;

};