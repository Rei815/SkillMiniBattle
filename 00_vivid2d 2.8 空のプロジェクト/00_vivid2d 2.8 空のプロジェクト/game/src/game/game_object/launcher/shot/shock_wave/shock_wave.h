#pragma once

#include "..\shot.h"
class CShockWave : public CShot
{
public:
    CShockWave();
    ~CShockWave();

private:
    static const BulletParameters        m_bullet_parameters;

};