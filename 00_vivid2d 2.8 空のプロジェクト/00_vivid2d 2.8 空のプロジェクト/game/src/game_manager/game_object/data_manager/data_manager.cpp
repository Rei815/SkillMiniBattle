#include "data_manager.h"
/*
 *  �C���X�^���X�̎擾
 */
CDataManager&
CDataManager::
GetInstance(void)
{
    static CDataManager instance;

    return instance;
}

/*
 *  ������
 */
void
CDataManager::
Initialize(void)
{
}

/*
 *  �X�V
 */
void
CDataManager::Update(void)
{

}

/*
 *  ���
 */
void CDataManager::Finalize(void)
{
}

/*
 *  �R���X�g���N�^
 */
CDataManager::
CDataManager(void)
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
CDataManager::
CDataManager(const CDataManager& rhs)
{
    (void)rhs;
}

/*
 *  �f�X�g���N�^
 */
CDataManager::
~CDataManager(void)
{
}

/*
 *  ������Z�q
 */
CDataManager&
CDataManager::
operator=(const CDataManager& rhs)
{
    (void)rhs;

    return *this;
}
