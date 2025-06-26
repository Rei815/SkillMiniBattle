#pragma once
#include "../../component/component.h"

#include "../../mathematics/mathematics.h"
#include "../../utility/utility.h"

#include <memory>
#include <vector> // vector��ǉ�
#include <map>
#include <typeindex>
#include <typeinfo>
#include <cassert>

class CGameObject
{
public:
    CGameObject();
    virtual ~CGameObject();

    // --- �R���|�[�l���g�Ǘ����\�b�h ---

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

    // --- ��{�I�ȃf�[�^�ւ̃A�N�Z�X ---
    // (�����͍ŏI�I��TransformComponent�Ɉڍs���邽�߁A������폜���܂�)
    virtual const CVector3& GetPosition() const { return m_Position; }
    virtual void SetPosition(const CVector3& position) { m_Position = position; }
    virtual CTransform GetTransform() const { return m_Transform; }
    virtual void SetTransform(const CTransform& transform) { m_Transform = transform; }

    virtual bool IsActive() const { return m_IsActive; }
    virtual void SetActive(bool active) { m_IsActive = active; }

protected:
    CVector3   m_Position;
    CTransform m_Transform;
    bool       m_IsActive;

private:
    std::map<std::type_index, std::vector<std::shared_ptr<IComponent>>> m_Components;
};