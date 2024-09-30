#pragma once

#include "..\shot.h"
class CFiveWay : public CShot
{
public:
    CFiveWay();
    ~CFiveWay();

    void Update(void) override;
private:

    static const BulletParameters        m_bullet_parameters;

};