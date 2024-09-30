#pragma once

#include "..\shot.h"
class CThreeWay : public CShot
{
public:
    CThreeWay();
    ~CThreeWay();

    void Update(void) override;
private:

    static const BulletParameters        m_bullet_parameters;

};