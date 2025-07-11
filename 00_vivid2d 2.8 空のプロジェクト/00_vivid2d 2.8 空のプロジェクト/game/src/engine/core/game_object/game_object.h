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

    /**
     * @brief �R���|�[�l���g��ǉ����܂��B�����^�̃R���|�[�l���g�������ǉ��ł��܂��B
     */
    template<typename T, typename... Args>
    std::shared_ptr<T> AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of<IComponent, T>::value, "T must inherit from IComponent");

        std::shared_ptr<T> component = std::make_shared<T>(std::forward<Args>(args)...);
        m_Components[typeid(T)].push_back(component);
        component->OnAttach(this);
        return component;
    }

    /**
     * @brief �w�肳�ꂽ�^�̍ŏ��̃R���|�[�l���g���擾���܂��B
     */
    template<typename T>
    std::shared_ptr<T> GetComponent() const
    {
        static_assert(std::is_base_of<IComponent, T>::value, "T must inherit from IComponent");

        auto it = m_Components.find(typeid(T));
        if (it != m_Components.end() && !it->second.empty())
        {
            return std::dynamic_pointer_cast<T>(it->second.front());
        }
        return nullptr;
    }

    /**
     * @brief �w�肳�ꂽ�^�̂��ׂẴR���|�[�l���g���x�N�^�[�Ŏ擾���܂��B
     */
    template<typename T>
    std::vector<std::shared_ptr<T>> GetComponents() const
    {
        static_assert(std::is_base_of<IComponent, T>::value, "T must inherit from IComponent");

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

    /**
     * @brief ����̃R���|�[�l���g�����Ȃ��Ƃ�1�����Ă��邩�m�F���܂��B
     */
    template<typename T>
    bool HasComponent() const
    {
        auto it = m_Components.find(typeid(T));
        return (it != m_Components.end() && !it->second.empty());
    }

    /**
     * @brief �w�肳�ꂽ�^�̃R���|�[�l���g�����ׂč폜���܂��B
     */
    template<typename T>
    void RemoveComponent()
    {
        static_assert(std::is_base_of<IComponent, T>::value, "T must inherit from IComponent");

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

    // --- ���C�t�T�C�N�����\�b�h ---
    virtual void Initialize();
    virtual void Update(float delta_time);
    virtual void Draw();
    virtual void Finalize();

    virtual bool IsActive() const { return m_IsActive; }
    virtual void Delete() { m_IsActive = false; }
    // --- ID�Ǘ����\�b�h��ǉ� ---
    void SetID(OBJECT_ID id) { m_Id = id; }
    OBJECT_ID GetID() const { return m_Id; }

    // --- �^�O�Ǘ����\�b�h ---
    void SetTag(GAME_OBJECT_TAG tag) { m_Tag = tag; }
    GAME_OBJECT_TAG GetTag() const { return m_Tag; }

    // --- �^�O�Ǘ����\�b�h ---
    void SetCategory(FACTION_CATEGORY category) { m_Category = category; }
    FACTION_CATEGORY GetCategory() const { return m_Category; }
protected:
    bool                m_IsActive;
    GAME_OBJECT_TAG       m_Tag; // �^�O��ێ����郁���o�[�ϐ�
    OBJECT_ID           m_Id; // �I�u�W�F�N�g��ID��ێ�
    FACTION_CATEGORY    m_Category;
private:
    std::map<std::type_index, std::vector<std::shared_ptr<IComponent>>> m_Components;
};