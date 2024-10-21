#include "model_manager.h"
const char* CModelManager::m_model_file_names[] =
{
    "data\\cube.mv1",
    "data\\flat_cube.mv1",
    "data\\Models\\cannon_test.mv1",
};

/*
 *  �C���X�^���X�̎擾
 */
CModelManager& CModelManager::GetInstance(void)
{
    static CModelManager instance;

    return instance;
}
/*
 *  �ǂݍ���
 */
void
CModelManager::Load(void)
{
    for (int i = 0; i < (int)MODEL_ID::MAX; ++i)
    {
        //// ���[�h�ς݂�3D���f��������
        //int handle = FindLoadedModel(m_model_file_names[i]);

        //// 3D���f������������
        //if (m_model_handles[i] != VIVID_DX_ERROR)
        //	return;

        //3D���f���̓ǂݍ���
        int handle = MV1LoadModel(m_model_file_names[i]);
        using namespace vivid::core;
        VIVID_DX_ASSERT(m_Handle, (TCHAR)m_model_file_names[i] + "�̓ǂݍ��݂Ɏ��s���܂����B");
        m_model_handles[i] = handle;
    }
}
void CModelManager::UnLoad(void)
{
    for (int i = 0; i < (int)MODEL_ID::MAX; ++i)
    {
        //�G���[
        if (m_model_handles[i] == VIVID_DX_ERROR)
            return;

        //�폜
        MV1DeleteModel(m_model_handles[i]);
    }

}
/*
 *  ������
 */
void
CModelManager::Initialize(void)
{
    m_ModelList.clear();
}

/*
 *  �X�V
 */
void
CModelManager::Update(void)
{
}

/*
 *  �`��
 */
void
CModelManager::Draw(void)
{
    if (m_ModelList.empty()) return;

    MODEL_LIST::iterator it = m_ModelList.begin();

    while (it != m_ModelList.end())
    {
        (*it)->Draw();

        ++it;
    }
}

/*
 *  ���
 */
void
CModelManager::Finalize(void)
{
    if (m_ModelList.empty()) return;

    MODEL_LIST::iterator it = m_ModelList.begin();

    while (it != m_ModelList.end())
    {
        (*it)->Finalize();

        delete (*it);

        ++it;
    }

    m_ModelList.clear();
}


/*
 *  �R���X�g���N�^
 */
CModelManager::CModelManager(void)
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
CModelManager::CModelManager(const CModelManager& rhs)
{
    (void)rhs;
}

/*
 *  �f�X�g���N�^
 */
CModelManager::
~CModelManager(void)
{
}

/*
 *  ������Z�q
 */
CModelManager& CModelManager::operator=(const CModelManager& rhs)
{
    (void)rhs;

    return *this;
}
