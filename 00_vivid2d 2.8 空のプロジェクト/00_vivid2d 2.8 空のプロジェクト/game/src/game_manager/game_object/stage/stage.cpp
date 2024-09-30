#include "stage.h"
#include <list>
#include "../bullet_manager/bullet_manager.h"

const int CStage::m_stage_height = 1500;
const int CStage::m_stage_width = 1500;
const int CStage::m_stage_debth = 1000;

CStage& CStage::GetInstance(void)
{
    static CStage instance;
    return instance;
}

void CStage::Initialize(void)
{
    m_Transform.position = CVector3(0, -60, -200);
    m_Model.Initialize("data\\Stage_1.mv1", m_Transform.position);

    //180度回転
    MV1SetRotationXYZ(m_Model.GetModelHandle(), CVector3(0.0f, DX_PI_F, 0.0f));

}

void CStage::Update(void)
{
	m_Model.Update(m_Transform);

}

void CStage::Draw(void)
{
	m_Model.Draw();

}

void CStage::Finalize(void)
{
	m_Model.Finalize();

}

CModel CStage::GetModel() const
{
    return m_Model;
}

void CStage::CheckHitUnit()
{

}
int CStage::GetHeight() const
{
    return m_stage_height;
}

int CStage::GetWidth() const
{
    return m_stage_width;
}

int CStage::GetDebth() const
{
    return m_stage_debth;
}


CStage::CStage()
    : m_Model()
    , m_Transform()
    , m_BoxCollider()
{
}

/*
 *  コピーコンストラクタ
 */
CStage::
CStage(const CStage& rhs)
{
    (void)rhs;
}

/*
 *  デストラクタ
 */
CStage::
~CStage(void)
{
}

/*
 *  代入演算子
 */
CStage&
CStage::
operator=(const CStage& rhs)
{
    (void)rhs;

    return *this;
}