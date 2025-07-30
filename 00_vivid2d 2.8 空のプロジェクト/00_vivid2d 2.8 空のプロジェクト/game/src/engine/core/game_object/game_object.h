#pragma once
#include "../component/component.h"
#include "../../mathematics/mathematics.h"
#include "../../utility/utility.h"

#include <memory>
#include <vector>
#include <map>
#include <typeindex>
#include <typeinfo>
#include <cassert>
#include "game_types.h"
#include "../../managers/object_manager/object_id.h"

class CGameObject
{
public:
    CGameObject();
    virtual ~CGameObject();

    /*
     * @brief �R���|�[�l���g�����̃Q�[���I�u�W�F�N�g�ɒǉ�
     * 
     * @param[in] T �ǉ�����R���|�[�l���g�̌^ (IComponent�h���N���X)
     * @param[in] Args �R���|�[�l���g�̃R���X�g���N�^�ɓn������
     * 
     * @return ��������A�ǉ����ꂽ�R���|�[�l���g�ւ̃|�C���^
     */
    template<typename T, typename... Args>
    std::shared_ptr<T> AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of<IComponent, T>::value, "�e���v���[�g���� T �� IComponent ���p�����Ă���K�v������܂�");

        std::shared_ptr<T> component = std::make_shared<T>(std::forward<Args>(args)...);
        m_Components[typeid(T)].push_back(component);
        component->OnAttach(this);
        return component;
    }

    /*
     * @brief �w�肳�ꂽ�^�̍ŏ��̃R���|�[�l���g���擾
     * 
     * @param[in] T �擾�������R���|�[�l���g�̌^
     * 
     * @return ���������R���|�[�l���g�ւ̃|�C���^ �Ȃ����nullptr
     */
    template<typename T>
    std::shared_ptr<T> GetComponent() const
    {
        static_assert(std::is_base_of<IComponent, T>::value, "�e���v���[�g���� T �� IComponent ���p�����Ă���K�v������܂�");

        auto it = m_Components.find(typeid(T));
        if (it != m_Components.end() && !it->second.empty())
        {
            return std::dynamic_pointer_cast<T>(it->second.front());
        }
        return nullptr;
    }

    /*
     * @brief �w�肳�ꂽ�^�̑S�ẴR���|�[�l���g���x�N�^�[�Ŏ擾
     * 
     * @param[in] T �擾�������R���|�[�l���g�̌^
     * 
     * @return ���������R���|�[�l���g�̃|�C���^���i�[����std::vector
     * ������Ȃ������ꍇ�́A��̃x�N�^�[��Ԃ�
     */
    template<typename T>
    std::vector<std::shared_ptr<T>> GetComponents() const
    {
        static_assert(std::is_base_of<IComponent, T>::value, "�e���v���[�g���� T �� IComponent ���p�����Ă���K�v������܂�");

        std::vector<std::shared_ptr<T>> result;
        auto it = m_Components.find(typeid(T));
        if (it != m_Components.end())
        {
            for (const auto& comp : it->second)
            {
                if (auto casted_comp = std::dynamic_pointer_cast<T>(comp))
                {
                    result.push_back(casted_comp);
                }
            }
        }
        return result;
    }

    /*
     * @brief ����̃R���|�[�l���g�����Ȃ��Ƃ�1�����Ă��邩�m�F
     * 
	 * @param[in] T �m�F�������R���|�[�l���g�̌^
     * 
	 * @return �w�肳�ꂽ�^�̃R���|�[�l���g�����݂���ꍇ��true�A���݂��Ȃ��ꍇ��false
     */
    template<typename T>
    bool HasComponent() const
    {
        auto it = m_Components.find(typeid(T));
        return (it != m_Components.end() && !it->second.empty());
    }

    /*
     * @brief �w�肳�ꂽ�^�̃R���|�[�l���g�����ׂč폜
     * 
	 * @param[in] T �폜�������R���|�[�l���g�̌^
     */
    template<typename T>
    void RemoveComponent()
    {
        static_assert(std::is_base_of<IComponent, T>::value, "�e���v���[�g���� T �� IComponent ���p�����Ă���K�v������܂�");

        auto it = m_Components.find(typeid(T));
        if (it != m_Components.end())
        {
            for (auto& component : it->second)
            {
                component->OnDetach(this);
            }
            m_Components.erase(it);
        }
    }

    // --- ���C�t�T�C�N�� ---
    virtual void Initialize();
    virtual void Update(float delta_time);
    virtual void Draw();
    virtual void Finalize();

    virtual bool IsActive() const { return m_IsActive; }
    virtual void Delete() { m_IsActive = false; }
    // --- ID�Ǘ� ---
    void SetID(OBJECT_ID id) { m_ID = id; }
    OBJECT_ID GetID() const { return m_ID; }

    // --- �^�O�Ǘ� ---
    void SetTag(GAME_OBJECT_TAG tag) { m_Tag = tag; }
    GAME_OBJECT_TAG GetTag() const { return m_Tag; }

    // --- �^�O�Ǘ� ---
    void SetCategory(FACTION_CATEGORY category) { m_Category = category; }
    FACTION_CATEGORY GetCategory() const { return m_Category; }

private:
	std::map<std::type_index, std::vector<std::shared_ptr<IComponent>>> m_Components; //!< �R���|�[�l���g�̃}�b�v
	bool                m_IsActive; //!< �I�u�W�F�N�g���A�N�e�B�u���ǂ����������t���O
    GAME_OBJECT_TAG     m_Tag;      //!< �^�O��ێ����郁���o�[�ϐ�
    OBJECT_ID           m_ID;       //!< �I�u�W�F�N�g��ID��ێ�
	FACTION_CATEGORY    m_Category; //!< �J�e�S���[��ێ����郁���o�[�ϐ�
};