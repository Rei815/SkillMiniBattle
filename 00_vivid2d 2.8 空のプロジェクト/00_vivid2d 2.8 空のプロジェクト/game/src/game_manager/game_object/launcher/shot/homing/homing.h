#pragma once

#include "..\shot.h"
class CHoming : public CShot
{
public:
    CHoming();
    ~CHoming();

private:
    static const BulletParameters        m_bullet_parameters;

};