#pragma once
#include "../../component/component.h"

#include "../../mathematics/mathematics.h"
#include "../../utility/utility.h"

#include <memory>    // std::shared_ptr �̂���
#include <map>       // �R���|�[�l���g�Ǘ��̂��߂� std::map �̂���
#include <typeindex> // �R���|�[�l���g�̌^�����L�[�Ƃ��Ďg������
#include <typeinfo>  // typeid ���g������
#include <cassert>   // static_assert �̂���


// CGameObject �N���X
// ���̃N���X�����ׂẴQ�[�����G���e�B�e�B�̊��ƂȂ�
class CGameObject
{
public:
    CGameObject(); // �R���X�g���N�^���`

    virtual ~CGameObject(); // �f�X�g���N�^�� virtual �ɂ��Ă���

    // --- �R���|�[�l���g�Ǘ����\�b�h ---

    // �R���|�[�l���g��ǉ�����
    template<typename T, typename... Args>
    std::shared_ptr<T> AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of<IComponent, T>::value, "T must inherit from IComponent");

        if (HasComponent<T>())
        {
            return GetComponent<T>();
        }

        std::shared_ptr<T> component = std::make_shared<T>(std::forward<Args>(args)...);
        m_Components[typeid(T)] = component; // �}�b�v�ɓo�^
        component->OnAttach(this); // �A�^�b�`���Ɏ��g�̃|�C���^��n��
        return component;
    }

    // �R���|�[�l���g���擾����
    template<typename T>
    std::shared_ptr<T> GetComponent() const
    {
        static_assert(std::is_base_of<IComponent, T>::value, "T must inherit from IComponent");

        auto it = m_Components.find(typeid(T));
        if (it != m_Components.end())
        {
            return std::dynamic_pointer_cast<T>(it->second);
        }
        return nullptr;
    }

    // ����̃R���|�[�l���g�������Ă��邩�m�F����
    template<typename T>
    bool HasComponent() const
    {
        return m_Components.count(typeid(T)) > 0; //
    }

    // �R���|�[�l���g���폜����
    template<typename T>
    void RemoveComponent()
    {
        static_assert(std::is_base_of<IComponent, T>::value, "T must inherit from IComponent");

        auto it = m_Components.find(typeid(T));
        if (it != m_Components.end())
        {
            it->second->OnDetach(this); // �R���|�[�l���g�̃f�^�b�`�������Ăяo��
            m_Components.erase(it); // �}�b�v����폜
        }
    }

    // --- ���C�t�T�C�N�����\�b�h ---
    virtual void Initialize(); //
    virtual void Update(float delta_time); // delta_time �������ɒǉ�
    virtual void Draw(); //
    virtual void Finalize(); //

    // --- ��{�I�ȃf�[�^�ւ̃A�N�Z�X ---
    virtual const CVector3& GetPosition() const { return m_Position; } //
    virtual void SetPosition(const CVector3& position) { m_Position = position; } //

    virtual CTransform GetTransform() const { return m_Transform; } //
    virtual void SetTransform(const CTransform& transform) { m_Transform = transform; } //

    virtual bool IsActive() const { return m_IsActive; } //
    virtual void SetActive(bool active) { m_IsActive = active; } //
protected:

    CVector3    m_Position;
    CTransform  m_Transform;

    bool        m_IsActive; //!< �A�N�e�B�u/��A�N�e�B�u��Ԃ��Ǘ�����t���O
private:
    // ���� GameObject ���A�^�b�`���Ă���R���|�[�l���g���Ǘ�����}�b�v
    // �L�[�̓R���|�[�l���g�̌^��� (typeid(T))�A�l�� shared_ptr<IComponent>
    std::map<std::type_index, std::shared_ptr<IComponent>> m_Components;



};